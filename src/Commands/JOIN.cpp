/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:34:41 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/06 12:44:08 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"
#include "Utilities.h"

void leave_all_channels(Command &cmd) {
  std::vector<Channel *> channels = cmd.get_server().get_channels();
  std::vector<Channel *>::iterator it;
  for (it = channels.begin(); it < channels.end(); ++it) {
    (*it)->broadcast(cmd.get_sender(), "PART " + (*it)->getName() +
                                           (cmd.get_arguments().size() > 1
                                                ? " :" + cmd.get_arguments()[1]
                                                : ""));
    (*it)->eraseUser(cmd.get_sender());
    if ((*it)->getUsers().size() == 0)
      cmd.get_server().delete_channel(*(*it));
  }
}

void JOIN(Command &cmd) {
  User &sender = cmd.get_sender();
  std::vector<std::string> arguments = cmd.get_arguments();
  if (sender.get_status() != USER_STATUS_ONLINE)
    return sender.reply(451);
  if (arguments.empty())
    return sender.reply(461, "JOIN");
  if (arguments[0] == "0")
    return leave_all_channels(cmd);
  std::vector<std::string> channels_name = Utilities::split(arguments[0], ",");
  for (std::vector<std::string>::iterator it = channels_name.begin();
       it != channels_name.end(); ++it) {
    if (it->c_str()[0] != '#') {
      sender.reply(476, *it);
      continue;
    }
    Channel &channel = cmd.get_server().get_channel(*it);
    if (channel.getUsers().size() == 0) {
      channel.addUser(sender);
      channel.setUserMode(sender, "O");
    } else {
      if (channel.getChannelMode().find('k') != std::string::npos) {
        sender.reply(475, *it);
        continue;
      }
      if (channel.getChannelMode().find('l') != std::string::npos) {
        sender.reply(471, *it);
        continue;
      }
      if (channel.getChannelMode().find('i') != std::string::npos &&
          !channel.isInvitedUser(sender) &&
          sender.get_user_mode().has_mode(USER_MODE_OPERATOR)) {
        sender.reply(473, *it);
        continue;
      }
      channel.eraseInvitedUser(sender);
      channel.addUser(sender);
    }
    std::string channel_mode;
    if (channel.getChannelMode().find('p') != std::string::npos)
      channel_mode = "*";
    else if (channel.getChannelMode().find('s') != std::string::npos)
      channel_mode = "@";
    else
      channel_mode = "=";
    if (channel.getTopic().length())
      sender.reply(332, *it, channel.getTopic());
    sender.reply(353, channel_mode, *it, users_to_string(channel));
    sender.reply(366, *it);
    channel.broadcast(sender, "JOIN :" + channel.getName());
  }
}
