/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:48:19 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/05 13:36:49 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"

std::string users_to_string(Channel channel) {
  std::vector<User *> users = channel.getUsers();
  std::string users_string = "";

  for (std::vector<User *>::iterator it = users.begin(); it != users.end();
       ++it) {
    if ((*it)->get_user_mode().has_mode(USER_MODE_INVISIBLE))
      continue;
    if (users_string.length())
      users_string += " ";
    if (channel.getUserMode(*(*it)).find('O') != std::string::npos ||
        channel.getUserMode(*(*it)).find('o') != std::string::npos)
      users_string += "@";
    users_string += (*it)->get_nickname();
  }
  return users_string;
}

void NAMES(Command &cmd) {
  std::vector<Channel *> channels = cmd.get_server().get_channels();
  std::vector<std::string> args = cmd.get_arguments();
  User &sender = cmd.get_sender();
  if (args.size() == 1) {
    Channel *channel = NULL;
    std::vector<Channel *>::iterator it;
    for (it = channels.begin(); it != channels.end(); ++it) {
      if ((*it)->getName() == args.at(0)) {
        channel = *it;
        break;
      }
    }
    if (channel != NULL) {
      std::string channel_mode;
      if (channel->getChannelMode().find('p') != std::string::npos)
        channel_mode = "*";
      else if (channel->getChannelMode().find('s') != std::string::npos)
        channel_mode = "@";
      else
        channel_mode = "=";
      std::string users_string = users_to_string(*channel);
      if (users_string.length())
        sender.reply(353, channel_mode, channel->getName(),
                     users_to_string(*channel));
      else
        sender.reply(366, args.at(0));
    }
  } else {
    std::vector<Channel *>::iterator it;
    for (it = channels.begin(); it != channels.end(); ++it) {
      Channel *channel = *it;
      if (channel->getChannelMode().find('p') != std::string::npos)
        continue;
      std::string channel_mode;
      if (channel->getChannelMode().find('s') != std::string::npos)
        channel_mode = "@";
      else
        channel_mode = "=";
      std::string users_string = users_to_string(*channel);
      if (users_string.length())
        sender.reply(353, channel_mode, channel->getName(),
                     users_to_string(*channel));
      sender.reply(366, channel->getName());
    }
    std::map<int, User *> users = cmd.get_server().get_users();
    std::string str = "";
    for (std::map<int, User *>::iterator it = users.begin(); it != users.end();
         ++it) {
      if (str.length())
        str += " ";
      str += (*it).second->get_nickname();
    }
    if (str.length()) {
      sender.reply(353, "", "*", str);
      sender.reply(366, "*");
    }
  }
}
