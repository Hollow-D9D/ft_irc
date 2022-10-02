/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:53:44 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 02:50:06 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.h"
#include "Command.h"
#include "Server.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

User::User(Server &server, int fd, const std::string &hostname,
           const std::string &hostaddr)
    : m_server(server), m_fd(fd), m_status(USER_STATUS_PASSWORD),
      m_hostname(hostname), m_hostaddr(hostaddr) {}

User::~User() {}

Server &User::get_server() { return m_server; }

int User::get_fd() const { return m_fd; }

UserStatus User::get_status() const { return m_status; }

const std::string &User::get_hostname() const { return m_hostname; }

const std::string &User::get_hostaddr() const { return m_hostaddr; }

const std::string &User::get_username() const { return m_username; }

const std::string &User::get_nickname() const { return m_nickname; }

const std::string &User::get_host() const {
  return m_hostname.empty() ? m_hostaddr : m_hostname;
}

std::string User::get_prefix() const {
  std::string prefix = m_nickname;
  const std::string &host = get_host();
  if (!host.empty()) {
    if (!m_username.empty())
      prefix += "!" + m_username;
    prefix += "@" + host;
  }
  return prefix;
}

void User::set_username(const std::string &username) { m_username = username; }

void User::set_nickname(const std::string &nickname) { m_nickname = nickname; }

void User::set_hostname(const std::string &hostname) { m_hostname = hostname; }

void User::set_hostaddr(const std::string &hostaddr) { m_hostaddr = hostaddr; }

void User::set_status(UserStatus status) { m_status = status; }

void User::write(const std::string &message) {
  std::string formatted = message + "\r\n";
  send(m_fd, formatted.data(), formatted.size(), 0);
}

void User::send_to(User &user, const std::string &message) {
  user.write(":" + get_prefix() + " " + message);
}

void User::broadcast(const std::string &message) {
  std::map<int, User *> &users = m_server.get_users();
  for (std::map<int, User *>::iterator it = users.begin(); it != users.end();
       ++it)
    send_to(*(it->second), message);
}

void User::handle() {

  if (m_status == USER_STATUS_DISCONNECTED)
    return;

  char buffer[BUFFER_SIZE];
  int size = recv(m_fd, buffer, BUFFER_SIZE, 0);

  if (size == -1)
    return;

  if (size == 0) {
    m_status = USER_STATUS_DISCONNECTED;
    return;
  }

  std::string message(buffer, size);
  message.erase(std::remove(message.begin(), message.end(), '\n'),
                message.end());

  Command command(m_server, *this, message);
  const std::map<std::string, CommandHandlerCallback> &commands =
      m_server.get_commands();
  std::map<std::string, CommandHandlerCallback>::const_iterator it =
      commands.find(command.get_prefix());
  if (it != commands.end()) {

    it->second(command);
  }

  // std::string password;

  // switch (m_status) {
  //   case USER_STATUS_PASSWORD:

  //   if (message.find("PASS", 0) != 0)
  //     break;

  //   std::cout << "'" << message.substr(5) << "' '" << server.get_password()
  //   << "'\n";

  //   if (message.substr(5) != server.get_password()) {
  //     m_status = USER_STATUS_REGISTER;
  //   }

  //   break;

  //   case USER_STATUS_REGISTER:

  //   if (message.find("USER", 0) == 0)
  //     set_username(message.substr(5));

  //   if (message.find("NICK", 0) == 0)
  //     set_nickname(message.substr(5));

  //   if (!m_nickname.empty() && !m_username.empty()) {
  //     m_status = USER_STATUS_ONLINE;
  //     write("Welcome!");
  //   }

  //   break;

  //   default:
  //   break;
  // }

  // std::cout << m_hostname << "@" << m_hostaddr << " " << message << "\n";
}
