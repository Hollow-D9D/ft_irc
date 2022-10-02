/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:23:43 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 02:36:28 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.h"
#include "Server.h"
#include "User.h"

void NICK(Command &command) {
  User &sender = command.get_sender();
  const std::vector<std::string> &arguments = command.get_arguments();

  if (arguments.empty() || sender.get_status() != USER_STATUS_REGISTER)
    return;

  std::string nick = "NICK :" + arguments[0];
  Server &server = command.get_server();
  std::map<int, User *> &users = server.get_users();
  for (std::map<int, User *>::iterator it = users.begin(); it != users.end();
       ++it)
    sender.send_to(*(it->second), nick);

  sender.set_nickname(arguments[0]);
}