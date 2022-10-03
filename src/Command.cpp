/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 23:33:16 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 21:08:12 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.h"
#include "Server.h"
#include <sstream>

const std::string &Command::get_message() const { return m_message; }

const std::vector<std::string> &Command::get_arguments() const {
  return m_arguments;
}

const std::string &Command::get_prefix() const { return m_prefix; }

const std::string &Command::get_raw() const { return m_raw; }

User &Command::get_sender() { return m_sender; }

Server &Command::get_server() { return m_server; }

std::string Command::to_string() const {
  std::string result = m_prefix;

  for (std::vector<std::string>::const_iterator it = m_arguments.begin();
       it != m_arguments.end(); ++it)
    result += " " + *it;

  if (!m_message.empty())
    result += " : " + m_message;

  return result;
}

Command::Command(Server &server, User &sender, std::string message)
    : m_server(server), m_sender(sender) {

  m_raw = message;
  size_t pos = message.find(":");
  if (pos != std::string::npos) {
    std::string temp = message.substr(0, pos);
    m_message = message.substr(pos + 1);
    message = temp;
  }

  std::stringstream ssin(message);
  while (ssin.good()) {
    std::string tmp;
    ssin >> tmp;
    m_arguments.push_back(tmp);
  }

  m_prefix = *(m_arguments.begin());
  m_arguments.erase(m_arguments.begin());

  for (size_t i = 0; i < m_prefix.size(); ++i)
    m_prefix[i] = std::toupper(m_prefix[i]);
}
