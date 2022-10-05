/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:50:16 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 11:52:19 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"
#include "Utilities.h"

void PART(Command &cmd) {
  if (cmd.get_arguments().size() == 0) {
    cmd.get_sender().reply(461, "PART");
    return;
  }
  std::vector<std::string> channels =
      Utilities::split(cmd.get_arguments()[0], ",");
  for (std::vector<std::string>::iterator it = channels.begin();
       it != channels.end(); ++it) {
    std::string &channel = *it;
    if (channel.size() == 0)
      continue;
    if (cmd.get_server().is_channel(channel)) {
      Channel &chan = cmd.get_server().get_channel(channel);
      if (!chan.isUser(cmd.get_sender())) {
        cmd.get_sender().reply(442, channel);
        continue;
      }
      chan.broadcast(
          cmd.get_sender(),
          "PART " + channel +
              (cmd.get_message().size() ? " :" + cmd.get_message() : ""));
      chan.eraseUser(cmd.get_sender());
      if (chan.getUsers().size() == 0)
        cmd.get_server().delete_channel(chan);
    } else
      cmd.get_sender().reply(403, channel);
  }
}
