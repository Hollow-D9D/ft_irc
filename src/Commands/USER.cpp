/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:51:42 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 02:52:31 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../User.h"
#include "../Command.h"
#include "../Server.h"

void USER(Command &command) {
  const std::vector<std::string> &arguments = command.get_arguments();
  User &sender = command.get_sender();
  if (arguments.empty() || arguments.size() < 3 || sender.get_status() != USER_STATUS_REGISTER )
    return ;
  sender.set_username(arguments[0]);
  sender.broadcast("USER :" + arguments[0]);
}