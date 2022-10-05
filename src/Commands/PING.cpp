/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:24:41 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/05 20:06:39 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.h"
#include "User.h"

void PING(Command &cmd) {
  std::vector<std::string> arguments = cmd.get_arguments();
  User &sender = cmd.get_sender();
  if (arguments.empty()) {
    sender.reply(409, "PING");
    return;
  }
  sender.send_to(sender, "PONG :" + arguments[0]);
}
