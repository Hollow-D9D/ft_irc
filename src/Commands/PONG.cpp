/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PONG.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavetyan <aavetyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:28:52 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/05 09:38:37 by aavetyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.h"
#include "User.h"
#include <ctime>

void PONG(Command &cmd) {
  std::vector<std::string> arguments = cmd.get_arguments();
  if (arguments.empty())
  {
    cmd.get_sender().reply(409, "PONG");
    return;
  }
  cmd.get_sender().set_last_ping(std::time(0));
}
