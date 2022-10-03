/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavetyan <aavetyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:34:47 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 12:08:25 by aavetyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.h"
#include "Command.h"
#include "User.h"
#include "Channel.hpp"
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

void PASS(Command &command);
void NICK(Command &command);

Server::Server(int port, const std::string &password)
    : m_port(port), m_password(password), m_listening_fd(-1) {
  m_commands["PASS"] = PASS;
  m_commands["NICK"] = NICK;
}

Server::~Server() {
  for (std::map<int, User *>::iterator it = m_users.begin();
       it != m_users.end(); ++it)
    delete it->second;
}

const std::string &Server::get_password() const { return m_password; }

int Server::get_port() const { return m_port; }

const std::map<std::string, CommandHandlerCallback>
Server::get_commands() const {
  return m_commands;
}

std::map<int, User *> &Server::get_users() { return m_users; }

int Server::init() {
  if (m_listening_fd != -1)
    return 0;

  m_listening_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (!m_listening_fd)
    throw std::runtime_error("Failed to create a socket.");

  // Allow reuse of port
  int enable = 1;
  if (setsockopt(m_listening_fd, SOL_SOCKET, SO_REUSEADDR, &enable,
                 sizeof(enable)) == -1)
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

  FD_ZERO(&m_master_fds);
  FD_SET(m_listening_fd, &m_master_fds);

  // Start listening to the socket
  if (listen(m_listening_fd, SOMAXCONN) == -1)
    throw std::runtime_error("Failed to listen.");

  std::cout << "Listening to 0.0.0.0:" << m_port << "\n";

  return 0;
}

void Server::handle() {

  fd_set clone = m_master_fds;
  int count = select(FD_SETSIZE, &clone, NULL, NULL, 0);

  if (count < 0)
    throw std::runtime_error("Failed to run select function.");

  for (int i = 0; i < FD_SETSIZE; ++i)
    if (FD_ISSET(i, &clone)) {
      if (i == m_listening_fd) {
        accept_new_connection();
        continue;
      }

      std::map<int, User *>::iterator it = m_users.find(i);
      if (it != m_users.end())
        it->second->handle();
    }

  // Cleanup
  for (std::map<int, User *>::iterator it = m_users.begin();
       it != m_users.end();) {
    User *user = it->second;
    if (user && user->get_status() == USER_STATUS_DISCONNECTED) {
      delete user;
      m_users.erase(it++);
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

  FD_SET(fd, &m_master_fds);
  m_users[fd] = new User(*this, fd, host, srv);
  return;
}

bool Server::make_socket_nonblocking(int fd) {
  int flag = fcntl(fd, F_GETFL, 0);
  if (flag == -1)
    return false;
  return fcntl(fd, F_SETFL, flag | O_NONBLOCK) != -1;
}


bool Server::is_channel(std::string const &name){
  return channels.count(name);
}

std::vector<Channel *> Server::get_channels(){
  std::map<std::string, Channel>::iterator it;
  std::vector<Channel *> channels;
  for (it = this->channels.begin(); it != this->channels.end(); ++it)
    channels.push_back(&(*it).second);
  return channels;
}

Channel &Server::get_channel(std::string &name)
{
  Channel &channel = this->channels[name];
  if (is_channel(name))
  {
    channel.setName(name);
    // display channel
  }
  return (channel);
}