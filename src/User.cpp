/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:53:44 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 15:37:07 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.h"
#include "Command.h"
#include "Response.h"
#include "Server.h"
#include <algorithm>
#include <iostream>
#include <sstream>
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

const Server &User::get_server() const { return m_server; }

int User::get_fd() const { return m_fd; }

UserStatus User::get_status() const { return m_status; }

const std::string &User::get_hostname() const { return m_hostname; }

const std::string &User::get_hostaddr() const { return m_hostaddr; }

const std::string &User::get_username() const { return m_username; }

const std::string &User::get_nickname() const { return m_nickname; }

const std::string &User::get_realname() const { return m_realname; }

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

std::time_t User::get_last_ping() const { return m_last_ping; }

void User::set_username(const std::string &username) { m_username = username; }

void User::set_nickname(const std::string &nickname) { m_nickname = nickname; }

void User::set_hostname(const std::string &hostname) { m_hostname = hostname; }

void User::set_hostaddr(const std::string &hostaddr) { m_hostaddr = hostaddr; }

void User::set_realname(const std::string &realname) { m_realname = realname; }

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

void User::set_last_ping(time_t last_ping) { m_last_ping = last_ping; }

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
    std::cout << "Command called: " << command.get_prefix() << "\n";
    it->second(command);
  }

  if (!m_nickname.empty() && !m_realname.empty()) {
    m_status = USER_STATUS_ONLINE;
    reply(001, m_username);
    reply(002, m_hostname, "1.0");
    reply(003, m_server.get_created_at_formatted());
    reply(004, "ft_irc", "1.0");
  }
}

void User::reply(int code, const std::string &arg0, const std::string &arg1,
                 const std::string &arg2, const std::string &arg3,
                 const std::string &arg4, const std::string &arg5,
                 const std::string &arg6) {
  std::ostringstream stream;
  std::string target =
      m_status == USER_STATUS_PASSWORD || m_status == USER_STATUS_REGISTER
          ? "*"
          : m_nickname;
  stream << ":server " << std::dec << code << " " << target << " "
         << Response::code_to_response(code, arg0, arg1, arg2, arg3, arg4, arg5,
                                       arg6);
  write(stream.str());
}
