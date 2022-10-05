/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:46:25 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/05 21:14:11 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"
#include <algorithm>

void NOTICE(Command &cmd) {
  const std::vector<std::string> &args = cmd.get_arguments();
  User &sender = cmd.get_sender();
  Server &server = cmd.get_server();
  if (!args.size() || !cmd.get_message().length())
    return;
  std::vector<User *> users;
  std::string getter = args.at(0);
  if (*getter.begin() == '#') {
    if (server.is_channel(getter)) {
      Channel &channel = server.get_channel(getter);
      if (!channel.isUser(sender))
        return;
      users = channel.getUsers();
      std::vector<User *>::iterator it =
          std::find(users.begin(), users.end(), &sender);
      if (it != users.end())
        users.erase(it);
    } else
      return;
  } else {
    if (server.get_user(getter))
      users.push_back(server.get_user(getter));
    else
      return;
  }
  std::vector<User *>::iterator it;
  for (it = users.begin(); it != users.end(); ++it)
    if (sender != *(*it))
      sender.send_to(*(*it), "NOTICE " + getter + " :" + cmd.get_message());
}
