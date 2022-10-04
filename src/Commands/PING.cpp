/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:24:41 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/03 15:44:58 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.h"
#include "User.h"

void PING(Command &cmd) {
  std::vector<std::string> arguments = cmd.get_arguments();
  if (arguments.empty()) {
    cmd.get_sender().reply(409, "PING");
    return;
  }
  cmd.get_sender().send_to(cmd.get_sender(), "PONG :" + arguments[0]);
}
