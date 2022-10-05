/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:37:24 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 14:25:39 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.h"
#include "Server.h"
#include "User.h"

void QUIT(Command &command) {
  User &sender = command.get_sender();
  if (!command.get_message().empty())
    sender.broadcast("QUIT :" + command.get_message());
  sender.set_status(USER_STATUS_DISCONNECTED);
}
