/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 23:33:16 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 02:20:39 by aabajyan         ###   ########.fr       */
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

User &Command::get_sender() { return m_sender; }

Server &Command::get_server() { return m_server; }

Command::Command(Server &server, User &sender, std::string message)
    : m_server(server), m_sender(sender) {

  size_t pos = message.find(":");
  if (pos != std::string::npos) {
    std::string tmp = message.substr(0, pos);
    message.erase(0, pos + 1);
    m_trailer = message;
    m_message = tmp;
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
