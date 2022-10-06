/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavetyan <aavetyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:36:37 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/06 19:59:33 by aavetyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utilities.h"
#include "Channel.hpp"
#include "User.h"
#include "UserMode.h"

std::vector<std::string> Utilities::split(std::string arg,
                                          const std::string &c) {
  std::vector<std::string> channels;
  size_t pos;
  while ((pos = arg.find(c)) != std::string::npos) {
    channels.push_back(arg.substr(0, pos));
    arg.erase(0, pos + 1);
  }
  channels.push_back(arg);
  return channels;
}

std::string users_to_string(Channel &channel) {
  std::vector<User *> users = channel.getUsers();
  std::string users_string = "";

  for (std::vector<User *>::const_iterator it = users.begin();
       it != users.end(); ++it) {
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
