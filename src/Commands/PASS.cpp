/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavetyan <aavetyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:16:14 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 14:47:05 by aavetyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.h"
#include "../Server.h"
#include "../User.h"

void PASS(Command &command) {
  User &sender = command.get_sender();
  const std::vector<std::string> &arguments = command.get_arguments();
  if (sender.get_status() != USER_STATUS_REGISTER)
    return;

  if (arguments.empty() || arguments[0].empty()) {
    sender.reply(431);
    return;
  }
  if (arguments.empty() || sender.get_status() != USER_STATUS_PASSWORD)
    return;

  const std::string &password = arguments[0];
  Server &server = command.get_server();

  if (server.get_password() == password)
    sender.set_status(USER_STATUS_REGISTER);
}
