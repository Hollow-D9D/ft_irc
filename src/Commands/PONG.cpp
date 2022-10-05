/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PONG.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:28:52 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/05 20:06:46 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.h"
#include "User.h"
#include <ctime>

void PONG(Command &cmd) {
  std::vector<std::string> arguments = cmd.get_arguments();
  if (arguments.empty()) {
    cmd.get_sender().reply(409, "PONG");
    return;
  }
}
