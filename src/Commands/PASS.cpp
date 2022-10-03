/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:16:14 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 15:22:54 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.h"
#include "../Server.h"
#include "../User.h"

void PASS(Command &command) {
  User &sender = command.get_sender();
  const std::vector<std::string> &arguments = command.get_arguments();

  if (sender.get_status() != USER_STATUS_PASSWORD)
    return;

  if (arguments.empty() || arguments[0].empty()) {
    sender.reply(431);
    return;
  }

  const std::string &password = arguments[0];
  Server &server = command.get_server();
  if (server.get_password() == password)
    sender.set_status(USER_STATUS_REGISTER);
}
