/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:01:32 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 02:12:02 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.h"

namespace Response {
std::string welcome(const std::string &nick, const std::string &user,
                    const std::string &host) {
  return ":Welcome to the Internet Relay Network " + nick + "!" + user + "@" +
         host + " ";
}

std::string your_host(const std::string &servername,
                      const std::string &version) {
  return ":Your host is " + servername + ", running version " + version + " ";
}

std::string created(const std::string &date) {
  return ":This server was created " + date;
}

std::string my_info(const std::string &server_name, const std::string &version,
                    const std::string &user_modes,
                    const std::string &channel_modes) {
  return server_name + " " + version + " " + user_modes + " " + channel_modes;
}

} // namespace Response