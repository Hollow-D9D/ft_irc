/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:53:44 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/06 12:38:03 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.h"
#include "Command.h"
#include "Common.h"
#include "Response.h"
#include "Server.h"
#include "Utilities.h"
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

User::User(Server &server, int fd, const std::string &hostname,
           const std::string &hostaddr)
    : m_server(server), m_fd(fd), m_status(USER_STATUS_PASSWORD),
      m_hostname(hostname), m_hostaddr(hostaddr), m_username(""),
      m_nickname(""), m_realname(""), m_last_ping(std::time(NULL)),
      m_queued_commands(), m_sending_queue(), m_user_mode() {}

User::~User() {
  std::cout << "FD: " << m_fd << " has been destroyed.\n";
  close(m_fd);
}

Server &User::get_server() { return m_server; }

const Server &User::get_server() const { return m_server; }

int User::get_fd() const { return m_fd; }

UserStatus User::get_status() const { return m_status; }

UserStatus User::get_previous_status() const { return m_previous_status; }

const std::string &User::get_hostname() const { return m_hostname; }

const std::string &User::get_hostaddr() const { return m_hostaddr; }

const std::string &User::get_username() const { return m_username; }

const std::string &User::get_nickname() const { return m_nickname; }

const std::string &User::get_realname() const { return m_realname; }

const std::string &User::get_host() const {
  return m_hostname.empty() ? m_hostaddr : m_hostname;
}

std::string User::get_prefix() const {
  if (m_nickname.empty())
    return "";
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

UserMode &User::get_user_mode() { return m_user_mode; }

void User::set_username(const std::string &username) { m_username = username; }

void User::set_nickname(const std::string &nickname) { m_nickname = nickname; }

void User::set_hostname(const std::string &hostname) { m_hostname = hostname; }

void User::set_hostaddr(const std::string &hostaddr) { m_hostaddr = hostaddr; }

void User::set_realname(const std::string &realname) { m_realname = realname; }

void User::set_status(UserStatus status) {
  m_previous_status = m_status;
  m_status = status;

  if (m_status == USER_STATUS_ONLINE) {
    std::string users_count = Utilities::to_string(m_server.get_users().size());
    reply(001, get_prefix());
    reply(002, m_hostname, "1.0");
    reply(003, m_server.get_created_at_formatted());
    reply(004, "ft_irc", "1.0", "aiwro", "Oovimnptkl");
    reply(251, users_count, "0");
    reply(252, "0");
    reply(253, "0");
    reply(254, Utilities::to_string(m_server.get_channels().size()));
    reply(255, users_count, "0");
  }
}

void User::write(const std::string &message) {
  m_sending_queue.push_back(message);
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

void User::push() {
  if (m_sending_queue.empty())
    return;

  std::string final_message = "";
  for (std::vector<std::string>::iterator it = m_sending_queue.begin();
       it != m_sending_queue.end(); ++it) {
    std::cout << "(" << m_fd << ")> " << *it << "\n";
    final_message += *it + CRLF;
  }
  m_sending_queue.clear();
  send(m_fd, final_message.data(), final_message.size(), 0);
}

void User::set_last_ping(time_t last_ping) { m_last_ping = last_ping; }

bool User::operator==(const User &other) const { return m_fd == other.m_fd; }

bool User::operator!=(const User &other) const { return m_fd != other.m_fd; }

void User::parse_messages() {

  char buffer[BUFFER_SIZE];
  int size = recv(m_fd, buffer, BUFFER_SIZE, 0);

  if (size == -1)
    return;

  if (size == 0) {
    broadcast("QUIT :Connection lost");
    set_status(USER_STATUS_DISCONNECTED);
    return;
  }

  buffer[size] = '\0';

  char *token = std::strtok(buffer, CRLF);
  while (token != NULL) {
    std::cout << "(" << m_fd << ")< " << token << "\n";
    m_queued_commands.push_back(
        new Command(m_server, *this, std::string(token)));
    token = std::strtok(NULL, CRLF);
  }
}

void User::handle() {

  if (m_status == USER_STATUS_DISCONNECTED)
    return;

  parse_messages();

  const std::map<std::string, CommandHandlerCallback> &commands =
      m_server.get_commands();
  while (!m_queued_commands.empty()) {
    Command *command = m_queued_commands[0];
    std::map<std::string, CommandHandlerCallback>::const_iterator it =
        commands.find(command->get_prefix());
    if (it != commands.end()) {
      it->second(*command);
    }
    delete command;
    m_queued_commands.erase(m_queued_commands.begin());
  }

  if (m_status == USER_STATUS_REGISTER && !m_nickname.empty() &&
      !m_realname.empty())
    set_status(USER_STATUS_ONLINE);
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
  stream << ":" << get_prefix() << " " << std::setfill('0') << std::setw(3)
         << code << " " << target << " "
         << Response::code_to_response(code, arg0, arg1, arg2, arg3, arg4, arg5,
                                       arg6);
  write(stream.str());
}
