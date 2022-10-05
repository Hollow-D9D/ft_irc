/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavetyan <aavetyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:23:43 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 10:47:04 by aavetyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.h"
#include "Server.h"
#include "User.h"

static bool isspecial(char c) {
  return (c >= '[' && c <= '`') || (c >= '{' && c <= '}');
}

static bool is_valid_nickname(const std::string &nickname) {
  if (!std::isalpha(nickname[0]))
    return false;
  for (size_t i = 1; i < nickname.size(); ++i)
    if (!std::isalnum(nickname[i]) && !isspecial(nickname[i]) &&
        nickname[i] != '-')
      return false;
  return true;
}

void NICK(Command &command) {
  User &sender = command.get_sender();
  const std::vector<std::string> &arguments = command.get_arguments();

  if (sender.get_status() != USER_STATUS_REGISTER)
    return;

  if (arguments.empty() || arguments[0].empty()) {
    sender.reply(431);
    return;
  }

  if (!is_valid_nickname(arguments[0])) {
    sender.reply(432);
    return;
  }

  if (command.get_server().find_user_by_nickname(arguments[0]) != NULL) {
    sender.reply(433, arguments[0]);
    return;
  }

  sender.broadcast("NICK :" + arguments[0]);
  sender.set_nickname(arguments[0]);
}
