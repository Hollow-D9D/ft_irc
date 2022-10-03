/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:08:20 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/03 22:07:10 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"

void PRIVMSG(Command &cmd) {
  const std::vector<std::string> &args = cmd.get_arguments();
  if (args.empty())
    return;
  std::vector<User *> users;
  std::string getter = args.at(0);
  if (*getter.begin() == '#') {
    Channel &channel = cmd.get_server().get_channel(getter);
    if (!channel.isUser(cmd.get_sender()))
      return;
    users = channel.getUsers();
    std::vector<User *>::iterator it;
    it = std::find(users.begin(), users.end(), &cmd.get_server());
    if (it == users.end())
      users.erase(it);
  } else {
    if (cmd.get_server().get_user(getter))
      users.push_back(cmd.get_server().get_user(getter));
    else
      return;
  }
  for (std::vector<User *>::iterator it = users.begin(); it != users.end();
       ++it)
    cmd.get_sender().send_to(*(*it),
                             "PRIVMSG " + getter + ":"); // + get trailer()
}