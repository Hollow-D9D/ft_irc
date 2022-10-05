/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WHO.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:50:00 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 18:11:57 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"

void WHO(Command &command) {
  User &sender = command.get_sender();
  Server &server = command.get_server();
  const std::vector<std::string> &arguments = command.get_arguments();
  if (sender.get_status() != USER_STATUS_ONLINE) {
    sender.reply(451);
    return;
  }

  if (arguments.empty()) {
    sender.reply(461, "WHO");
    return;
  }

  std::string name = arguments[0];
  if (name[0] == '#') {
    Channel *channel = server.get_channel_if_exists(name);
    if (channel == NULL) {
      sender.reply(403, name);
      return;
    }

    std::string users = channel->getNicknames(sender.get_nickname());

    sender.reply(315, users);
    return;
  }
}
