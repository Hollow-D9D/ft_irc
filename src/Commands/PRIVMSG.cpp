/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:08:20 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/03 22:12:02 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"
#include <algorithm>

void PRIVMSG(Command &cmd) {
  User &sender = cmd.get_sender();
  const std::vector<std::string> &args = cmd.get_arguments();
  if (args.empty())
    return;
  std::vector<User *> users;
  std::string getter = args.at(0);
  // if (*getter.begin() == '#') {
  //   Channel &channel = server.get_channel(getter);
  //   if (!channel.isUser(sender))
  //     return;
  //   users = channel.getUsers();
  //   std::vector<User *>::iterator it;
  //   it = std::find(users.begin(), users.end(), server);
  //   if (it == users.end())
  //     users.erase(it);
  // } else {
  //   if (server.get_user(getter))
  //     users.push_back(server.get_user(getter));
  //   else
  //     return;
  // }
  sender.broadcast("PRIVMSG " + getter + ":");
}