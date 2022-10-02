/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 23:33:18 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 02:32:06 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <string>
#include <vector>

class User;
class Server;
class Command {
public:
  Command(Server &server, User &sender, std::string message);

  const std::string &get_message() const;
  const std::vector<std::string> &get_arguments() const;
  const std::string &get_prefix() const;
  User &get_sender();
  Server &get_server();

private:
  Server &m_server;
  User &m_sender;
  std::vector<std::string> m_arguments;
  std::string m_message;
  std::string m_trailer;
  std::string m_prefix;
};

#endif // __COMMAND_H__
