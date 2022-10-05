/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:34:41 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/05 12:08:10 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"

void JOIN(Command &cmd) {
  User &sender = cmd.get_sender();
  if (sender.get_status() != USER_STATUS_ONLINE) {
    sender.reply(451);
    return;
  }

  std::vector<std::string> arguments = cmd.get_arguments();
  if (arguments.empty())
    return;
  std::vector<std::string> channels_name;
  size_t pos;
  while ((pos = arguments[0].find(',')) != std::string::npos) {
    channels_name.push_back(arguments[0].substr(0, pos));
    arguments[0].erase(0, pos + 1);
  }
  channels_name.push_back(arguments[0]);
  for (std::vector<std::string>::iterator it = channels_name.begin();
       it != channels_name.end(); ++it) {
    Channel &channel = cmd.get_server().get_channel(*it);
    channel.addUser(sender);
    sender.reply(353, channel.getChannelMode(), channel.getName(),
                 channel.getNicknames());
    sender.reply(366, channel.getName());
    channel.broadcast(sender, "JOIN :" + channel.getName());
  }
}
