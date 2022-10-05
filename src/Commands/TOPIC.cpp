/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:50:05 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 23:15:21 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"

void TOPIC(Command &cmd) {
  if (!cmd.get_arguments().size())
    return cmd.get_sender().reply(461, "TOPIC");
  if (!cmd.get_server().is_channel(cmd.get_arguments()[0]))
    return cmd.get_sender().reply(442, cmd.get_arguments()[0]);
  Channel &channel = cmd.get_server().get_channel(cmd.get_arguments()[0]);
  if (!channel.isUser(cmd.get_sender()))
    return cmd.get_sender().reply(442, cmd.get_arguments()[0]);

  if (cmd.get_raw().find(':') != std::string::npos) {
    bool canEdit = false;
    if (cmd.get_sender().get_user_mode().has_mode(USER_MODE_OPERATOR))
      canEdit = true;
    if (!canEdit)
      return cmd.get_sender().reply(482, channel.getName());
    channel.setTopic(cmd.get_message());
    return channel.broadcast(cmd.get_sender(), "TOPIC " + channel.getName() +
                                                   " :" + channel.getTopic());
  }

  if (!channel.getTopic().length())
    return cmd.get_sender().reply(331, channel.getName());
  return cmd.get_sender().reply(332, cmd.get_arguments()[0],
                                channel.getTopic());
}
