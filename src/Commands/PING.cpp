/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavetyan <aavetyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:24:41 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/03 14:35:34 by aavetyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.h"
#include "../User.h"


void PING(Command &cmd)
{
    std::vector<std::string> arguments = cmd.get_arguments();
    if (arguments.empty())
        return ;
    cmd.get_sender().send_to(cmd.get_sender(), "PONG :" + arguments[0]);
}
