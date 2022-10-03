/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:51:42 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 15:26:21 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.h"
#include "Command.h"
#include "Server.h"
#include <iostream>

void USER(Command &command) {
  User &sender = command.get_sender();
  UserStatus status = sender.get_status();
  const std::vector<std::string> &arguments = command.get_arguments();

  if (status == USER_STATUS_PASSWORD)
    return;

  if (arguments.size() < 3) {
    sender.reply(461);
    return;
  }

  if (status != USER_STATUS_REGISTER) {
    sender.reply(462);
    return;
  }

  std::cout << "prefix: " << command.get_prefix() << "\n";
  std::cout << "arguments: ";
  for (std::vector<std::string>::const_iterator it = arguments.begin();
       it != arguments.end(); ++it)
    std::cout << *it << "\n";
  std::cout << "message: " << command.get_message() << "\n";

  sender.set_username(arguments[0]);
  sender.set_realname(command.get_message());
}