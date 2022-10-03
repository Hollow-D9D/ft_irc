/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:08:20 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/03 15:43:37 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"

void PRIVMSG(Command &cmd) {

  const std::vector<std::string> &args = cmd.get_arguments();
  //   std::vector<User *> users;
  //   const std::vector<std::string> args = cmd.get_arguments();
  //   if (args.empty())
  //     return;
  //   if (*args.begin() == '#') {
  //     Channel &channel = cmd.get_server().get
  //   }
}