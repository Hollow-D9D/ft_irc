/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavetyan <aavetyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:50:58 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 15:00:13 by aavetyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"
#include "Utilities.h"
#include <vector>

// Copied method it's 4 AM
static bool strmatch(std::string str, std::string pattern) {
  size_t str_size = str.size();
  size_t pattern_size = pattern.size();

  if (str_size == 0 || pattern_size == 0)
    return false;
  std::vector<std::vector<bool> > lookup(
      str_size + 1, std::vector<bool>(pattern_size + 1, false));

  lookup[0][0] = true;

  for (size_t j = 1; j <= pattern_size; j++)
    if (pattern[j - 1] == '*')
      lookup[0][j] = lookup[0][j - 1];

  for (size_t i = 1; i <= str_size; i++) {
    for (size_t j = 1; j <= pattern_size; j++) {
      if (pattern[j - 1] == '*')
        lookup[i][j] = lookup[i][j - 1] || lookup[i - 1][j];
      else if (pattern[j - 1] == '?' || str[i - 1] == pattern[j - 1])
        lookup[i][j] = lookup[i - 1][j - 1];
      else
        lookup[i][j] = false;
    }
  }

  return lookup[str_size][pattern_size];
}

void LIST(Command &cmd) {
  std::vector<Channel *> channels = cmd.get_server().get_channels();
  if (cmd.get_arguments().size() == 1 && cmd.get_arguments()[0] != "") {
    for (std::vector<Channel *>::iterator it = channels.begin();
         it != channels.end(); ++it)
      if (strmatch((*it)->getName(), cmd.get_arguments()[0]))
        cmd.get_sender().reply(322, (*it)->getName(),
                               "" + Utilities::to_string((*it)->getUsers().size()),
                               (*it)->getTopic());
  } else
    for (std::vector<Channel *>::iterator it = channels.begin();
         it != channels.end(); ++it)
      cmd.get_sender().reply(322, (*it)->getName(),
                             "" + Utilities::to_string((*it)->getUsers().size()),
                             (*it)->getTopic());
  cmd.get_sender().reply(323);
}
