/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:34:47 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 23:15:19 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.h"
#include "Channel.hpp"
#include "Command.h"
#include "Common.h"
#include "User.h"
#include "Utilities.h"
#include <arpa/inet.h>
#include <cerrno>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <netdb.h>
#include <stdexcept>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void PASS(Command &);
void NICK(Command &);
void USER(Command &);
void PING(Command &);
void CAP(Command &);
void JOIN(Command &);
void KICK(Command &);
void PONG(Command &);
void PRIVMSG(Command &);
void NOTICE(Command &);
void QUIT(Command &);
void WHO(Command &);
void MODE(Command &);
void WHOIS(Command &);
void TOPIC(Command &);
void INVITE(Command &);
void NAMES(Command &);
void LIST(Command &);

Server::Server(int port, const std::string &password)
    : m_port(port), m_password(password), m_listening_fd(-1), m_master_fds(),
      m_created_at(std::time(NULL)), m_pinged_at(std::time(NULL)), m_users(),
      m_commands(), m_channels() {
  m_commands["PASS"] = PASS;
  m_commands["JOIN"] = JOIN;
  m_commands["KICK"] = KICK;
  m_commands["PONG"] = PONG;
  m_commands["PRIVMSG"] = PRIVMSG;
  m_commands["NOTICE"] = NOTICE;
  m_commands["NICK"] = NICK;
  m_commands["KICK"] = KICK;
  m_commands["USER"] = USER;
  m_commands["PING"] = PING;
  m_commands["QUIT"] = QUIT;
  m_commands["WHO"] = WHO;
  m_commands["MODE"] = MODE;
  m_commands["WHOIS"] = WHOIS;
  m_commands["TOPIC"] = WHOIS;
  m_commands["INVITE"] = INVITE;
  m_commands["NAMES"] = NAMES;
  m_commands["LIST"] = LIST;
}

Server::~Server() {
  for (std::map<int, User *>::iterator it = m_users.begin();
       it != m_users.end(); ++it)
    delete it->second;
  for (std::map<std::string, Channel *>::iterator it = m_channels.begin();
       it != m_channels.end(); ++it)
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

  std::cout << "Listening to " << inet_ntoa(hint.sin_addr) << ":" << m_port
            << "\n";

  return 0;
}

User *Server::get_user(const std::string &name) {
  for (std::map<int, User *>::iterator it = m_users.begin();
       it != m_users.end(); ++it) {
    if ((*it).second->get_nickname() == name)
      return (*it).second;
  }
  return NULL;
}

bool Server::handle() {

  fd_set clone = m_master_fds;
  int count = select(FD_SETSIZE, &clone, NULL, NULL, 0);

  if (count < 0)
    return false;

  for (int i = 0; i < FD_SETSIZE; ++i)
    if (FD_ISSET(i, &clone)) {
      if (i == m_listening_fd) {
        accept_new_connection();
        continue;
      }

      std::map<int, User *>::iterator it = m_users.find(i);
      if (it != m_users.end() &&
          it->second->get_status() != USER_STATUS_DISCONNECTED) {
        it->second->handle();
        it->second->set_last_ping(std::time(NULL));
      }
    }

  // Check for timeout
  std::time_t now = std::time(NULL);
  if (now - m_pinged_at > PING_TIMEOUT)
    for (std::map<int, User *>::iterator it = m_users.begin();
         it != m_users.end(); ++it)
      if (it->second->get_status() != USER_STATUS_DISCONNECTED &&
          now - it->second->get_last_ping() > USER_TIMEOUT) {
        it->second->broadcast("QUIT :Connection timeout");
        it->second->set_status(USER_STATUS_DISCONNECTED);
      }

  // Remove disconnected users and empty channels
  for (std::map<int, User *>::iterator it = m_users.begin();
       it != m_users.end();) {
    User *user = it->second;

    if (!user) {
      ++it;
      continue;
    }

    user->push();

    if (user->get_status() == USER_STATUS_DISCONNECTED) {
      for (std::map<std::string, Channel *>::iterator cit = m_channels.begin();
           cit != m_channels.end();) {
        cit->second->eraseUser(*user);
        if (cit->second->getUsers().empty()) {
          std::cout << "Channel " << cit->second->getName()
                    << " has no users, removing.\n";
          delete cit->second;
          m_channels.erase(cit++);
        } else
          ++cit;
      }
      FD_CLR(user->get_fd(), &m_master_fds);
      delete user;
      m_users.erase(it++);
    } else
      ++it;
  }

  return true;
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

  char host[NI_MAXHOST];
  char srv[NI_MAXSERV];
  if (getnameinfo(&in_addr, in_len, host, NI_MAXHOST, srv, NI_MAXSERV, 0) ==
      0) {
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

std::time_t Server::get_created_at() const { return m_created_at; }

std::string Server::get_created_at_formatted() const {
  char buffer[256];
  tm *timeinfo = localtime(&m_created_at);
  size_t size =
      strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", timeinfo);
  return std::string(buffer, size);
}

bool Server::make_socket_nonblocking(int fd) {
  return fcntl(fd, F_SETFL, O_NONBLOCK) != -1;
}

bool Server::is_channel(std::string const &name) const {
  return m_channels.count(name);
}

void Server::delete_channel(Channel &chan) { m_channels.erase(chan.getName()); }

std::vector<Channel *> Server::get_channels() {
  std::map<std::string, Channel *>::iterator it;
  std::vector<Channel *> channels;
  for (it = m_channels.begin(); it != m_channels.end(); ++it)
    channels.push_back(it->second);
  return channels;
}

Channel &Server::get_channel(const std::string &name) {
  std::map<std::string, Channel *>::iterator it = m_channels.find(name);
  if (it != m_channels.end())
    return *it->second;
  m_channels[name] = new Channel();
  m_channels[name]->setName(name);
  return *m_channels[name];
}

Channel *Server::get_channel_if_exists(const std::string &name) {
  std::map<std::string, Channel *>::iterator it = m_channels.find(name);
  return it != m_channels.end() ? it->second : NULL;
}

User *Server::find_user_by_nickname(const std::string &nickname) const {
  for (std::map<int, User *>::const_iterator it = m_users.begin();
       it != m_users.end(); ++it)
    if (it->second->get_nickname() == nickname)
      return it->second;
  return NULL;
}
