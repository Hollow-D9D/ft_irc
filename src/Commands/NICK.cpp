/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:23:43 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 02:49:08 by aabajyan         ###   ########.fr       */
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

  sender.broadcast("NICK :" + arguments[0]);
  sender.set_nickname(arguments[0]);
}