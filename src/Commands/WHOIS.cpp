/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WHOIS.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:49:57 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 12:08:34 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"

void WHOIS(Command &command) {
  Server &server = command.get_server();
  User &sender = command.get_sender();
  const std::vector<std::string> &arguments = command.get_arguments();

  if (sender.get_status() != USER_STATUS_ONLINE) {
    sender.reply(451);
    return;
  }

  if (arguments.empty()) {
    sender.reply(461, "WHOIS");
    return;
  }

  User *target = server.find_user_by_nickname(arguments[0]);
  if (!target) {
    sender.reply(401, arguments[0]);
    return;
  }

  sender.reply(311, target->get_nickname(), target->get_username(),
               target->get_host(), target->get_realname());
}
