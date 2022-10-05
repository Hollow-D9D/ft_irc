/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:50:26 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 18:11:57 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"

void MODE(Command &command) {
  User &sender = command.get_sender();
  Server &server = command.get_server();
  UserMode &user_mode = sender.get_user_mode();
  if (sender.get_status() != USER_STATUS_ONLINE) {
    sender.reply(451);
    return;
  }

  const std::vector<std::string> &arguments = command.get_arguments();
  if (arguments.size() < 1) {
    sender.reply(461, "MODE");
    return;
  }

  if (arguments[0][0] == '#') {
    Channel *channel = server.get_channel_if_exists(arguments[0]);
    if (!channel) {
      sender.reply(401, arguments[0]);
      return;
    }

    sender.reply(324, channel->getName(), "+" + channel->getMode());
    return;
  }

  if (arguments.size() >= 2) {
    User *target = server.find_user_by_nickname(arguments[0]);
    if (!target) {
      sender.reply(401, arguments[0]);
      return;
    }

    if (*target != sender) {
      sender.reply(502, arguments[0]);
      return;
    }

    user_mode.set_mode(arguments[1]);
  }

  sender.reply(221, user_mode.to_string());
}
