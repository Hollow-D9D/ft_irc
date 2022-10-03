/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:10:59 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/03 15:45:15 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"

std::vector<std::string> split(std::string arg, std::string c) {
  std::vector<std::string> channels;
  size_t pos;
  while ((pos = arg.find(c)) != std::string::npos) {
    channels.push_back(arg.substr(0, pos));
    arg.erase(0, pos + 1);
  }
  channels.push_back(arg);
  return channels;
}

void KICK(Command &cmd) {
  std::vector<std::string> arguments = cmd.get_arguments();
  if (arguments.empty())
    return;
  std::vector<std::string> channels = split(arguments[0], ",");
  std::vector<std::string> users = split(arguments[1], ",");
  std::vector<std::string>::iterator it;
  for (it = channels.begin(); it != channels.end(); ++it) {
    if (!cmd.get_server().is_channel(*it)) {
      cmd.get_sender().reply(403, *it);
      continue;
    }
    Channel &channel = cmd.get_server().get_channel(*it);
    std::vector<std::string>::iterator it2;
    for (it2 = users.begin(); it2 != users.end(); ++it2) {
      if (!channel.inChannel(*it2)) {
        cmd.get_sender().reply(441, *it2, *it);
        continue;
      }
      channel.broadcast(cmd.get_sender(),
                        "KICK :" + *it + " " + *it2 + " :" + arguments[2]);
      channel.eraseUser(*it2);
    }
  }
}
