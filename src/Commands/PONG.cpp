/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PONG.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavetyan <aavetyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:28:52 by aavetyan          #+#    #+#             */
/*   Updated: 2022/10/03 14:35:31 by aavetyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>
#include "../Command.h"
#include "../User.h"


void PONG(Command &cmd)
{
    std::vector<std::string> arguments = cmd.get_arguments();
    if (arguments.empty())
        return ;
    cmd.get_sender().set_last_ping(std::time(0));
}
