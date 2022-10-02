/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:53:44 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/02 23:38:36 by aabajyan         ###   ########.fr       */
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

User::User(int fd, const std::string &hostname, const std::string &hostaddr)
    : m_fd(fd), m_status(USER_STATUS_PASSWORD), m_hostname(hostname),
      m_hostaddr(hostaddr) {}

User::~User() {}

int User::get_fd() const { return m_fd; }

UserStatus User::get_status() const { return m_status; }

const std::string &User::get_hostname() const { return m_hostname; }
const std::string &User::get_hostaddr() const { return m_hostaddr; }

const std::string &User::get_username() const { return m_username; }
const std::string &User::get_nickname() const { return m_nickname; }

void User::set_username(const std::string &username) { m_username = username; }
void User::set_nickname(const std::string &nickname) { m_nickname = nickname; }

void User::reply(const std::string &message) {
  std::string formatted = message + "\r\n";
  send(m_fd, formatted.data(), formatted.size(), 0);
}

void User::handle(const Server &server) {

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

  Command command(message);

  std::cout << command.get_message() << "\n";

  const std::vector<std::string> &args = command.get_arguments();

  for (size_t i = 0; i < args.size(); ++i)
    std::cout << args[i] << "\n";

  std::cout << command.get_prefix() << "\n";

  (void)server;

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
  //     reply("Welcome!");
  //   }

  //   break;

  //   default:
  //   break;
  // }

  // std::cout << m_hostname << "@" << m_hostaddr << " " << message << "\n";
}
