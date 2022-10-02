/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:34:47 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/02 17:14:30 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.h"
#include "User.h"
#include <arpa/inet.h>
#include <cerrno>
#include <fcntl.h>
#include <iostream>
#include <netdb.h>
#include <stdexcept>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

Server::Server(int port, std::string password)
    : m_port(port), m_password(password), m_listening_fd(-1), m_epoll_fd(-1),
      m_epoll_event(), m_events() {}

Server::~Server() {
  for (std::vector<User *>::iterator it = m_users.begin(); it != m_users.end();
       ++it)
    delete *it;
}

int Server::init() {
  if (m_listening_fd != -1)
    return 0;

  m_listening_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (!m_listening_fd)
    throw std::runtime_error("Failed to create a socket.");

  // Allow reuse of port
  int enable = 1;
  if (setsockopt(m_listening_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                 &enable, sizeof(enable)) == -1)
    throw std::runtime_error("Failed to allow reuse of port.");

  // Make listening socket non blocking.
  if (!make_socket_nonblocking(m_listening_fd))
    throw std::runtime_error("Failed to set socket non blocking.");

  // Bind the socket to IP/PORT
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port = htons(m_port);
  hint.sin_addr.s_addr = INADDR_ANY;

  if (bind(m_listening_fd, (sockaddr *)&hint, sizeof(hint)) == -1)
    throw std::runtime_error("Failed to bind IP/Port to the socket.");

  // Create epoll file descriptor
  m_epoll_fd = epoll_create1(0);
  if (m_epoll_fd == -1)
    throw std::runtime_error("Failed to create epoll fd.");

  // Set flags for epoll event
  if (!add_socket_to_epoll(m_listening_fd))
    throw std::runtime_error("Failed to set flags for epoll.");

  // Start listening to the socket
  if (listen(m_listening_fd, SOMAXCONN) == -1)
    throw std::runtime_error("Failed to listen.");

  std::cout << "Listening to 0.0.0.0:" << m_port << "\n";

  return 0;
}

void Server::handle() {

  int n = epoll_wait(m_epoll_fd, m_events, SERVER_MAX_CONNECTIONS, -1);

  for (int i = 0; i < n; ++i) {
    epoll_event &event = m_events[i];

    // Check whenever it's a invalid event, if so close the fd.
    if (event.events & EPOLLERR || event.events & EPOLLHUP ||
        !(event.events & EPOLLIN)) {
      std::cerr << "Info: Epoll event error\n";
      close(event.data.fd);
      continue;
    }

    // If the fd is equal to listening fd then there's a new connection.
    if (event.data.fd == m_listening_fd) {
      accept_new_connection();
      continue;
    }

    User *user = find_user_by_fd(event.data.fd);
    if (user)
      user->handle();
  }

  // Cleanup
  for (std::vector<User *>::iterator it = m_users.begin();
       it != m_users.end();) {
    User *user = *it;
    if (user && user->get_status() == USER_STATUS_DISCONNECTED) {
      epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, user->get_fd(), NULL);
      delete user;
      it = m_users.erase(it);
    } else
      ++it;
  }
}

void Server::accept_new_connection() {
  sockaddr in_addr;
  socklen_t in_len = sizeof(in_addr);
  int fd = accept(m_listening_fd, &in_addr, &in_len);
  if (fd == -1) {
    if (!(errno == EAGAIN || errno == EWOULDBLOCK))
      std::cerr << "Error: Failed to accept a new connection.";
    return;
  }

  std::string host(NI_MAXHOST, '\0');
  std::string srv(NI_MAXSERV, '\0');
  if (getnameinfo(&in_addr, in_len, const_cast<char *>(host.c_str()),
                  host.size(), const_cast<char *>(srv.c_str()), srv.size(),
                  0) == 0) {
    std::cout << "Info: New connection: fd = " << fd << " " << host << "@"
              << srv << ".\n";
  }

  if (!make_socket_nonblocking(fd)) {
    std::cerr << "Error: Failed to set file descriptior " << fd
              << " non blocking.\n";
    return;
  }

  if (!add_socket_to_epoll(fd)) {
    std::cerr << "Error: Failed to add socket to epoll event.\n";
    return;
  }

  m_users.push_back(new User(fd));

  return;
}

bool Server::make_socket_nonblocking(int fd) {
  int flag = fcntl(fd, F_GETFL, 0);
  if (flag == -1)
    return false;
  return fcntl(fd, F_SETFL, flag | O_NONBLOCK) != -1;
}

bool Server::add_socket_to_epoll(int fd) {
  m_epoll_event.data.fd = fd;
  m_epoll_event.events = EPOLLIN | EPOLLET;
  return epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, fd, &m_epoll_event) != -1;
}

User *Server::find_user_by_fd(int fd) {
  for (std::vector<User *>::iterator it = m_users.begin(); it != m_users.end();
       ++it) {
    User *user = *it;
    if (user->get_fd() == fd)
      return user;
  }
  return NULL;
}
