/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavetyan <aavetyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:10:59 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/06 19:57:10 by aavetyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"
#include "Utilities.h"

void KICK(Command &cmd) {
  std::vector<std::string> arguments = cmd.get_arguments();
  if (arguments.empty())
    return cmd.get_sender().reply(403, "KICK");
  std::vector<std::string> channels = Utilities::split(arguments[0], ",");
  std::vector<std::string> users = Utilities::split(arguments[1], ",");
  std::vector<std::string>::iterator it;
  for (it = channels.begin(); it != channels.end(); ++it) {
    if (!cmd.get_server().is_channel(*it)) {
      cmd.get_sender().reply(403, *it);
      continue;
    }
    Channel &channel = cmd.get_server().get_channel(*it);
    if (channel.getUserMode(cmd.get_sender()).find('O') == std::string::npos &&
        channel.getUserMode(cmd.get_sender()).find('o') == std::string::npos &&
        cmd.get_sender().get_user_mode().has_mode(USER_MODE_OPERATOR))
      return cmd.get_sender().reply(482, *it);
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
