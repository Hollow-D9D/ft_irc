/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavetyan <aavetyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:08:20 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/05 10:46:06 by aavetyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"

void PRIVMSG(Command &cmd) {
  Server &server = cmd.get_server();
  User &sender = cmd.get_sender();
  const std::vector<std::string> &args = cmd.get_arguments();
  if (args.empty())
    return sender.reply(411, "PRIVMSG");
  std::vector<User *> users;
  std::string getter = args.at(0);
  if (*getter.begin() == '#') {
    if (server.is_channel(getter)){
      Channel &channel = server.get_channel(getter);
      if (!channel.isUser(sender))
        return sender.reply(404, channel.getName());
      users = channel.getUsers();
      std::vector<User *>::iterator it = find(users.begin(), users.end(), &sender);
      if (it != users.end())
        users.erase(it);
    }
    else
      return sender.reply(404, getter);
  } else {
    if (server.get_user(getter))
      users.push_back(server.get_user(getter));
    else
      return sender.reply(401, getter);
  }
  for (std::vector<User *>::iterator it = users.begin(); it != users.end();
       ++it)
    if (sender != *(*it))
      sender.send_to(*(*it),
                     "PRIVMSG " + getter + " :" +
                         cmd.get_message());
}
