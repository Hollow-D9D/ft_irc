/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:01:32 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 11:28:42 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.h"

namespace Response {
std::string RPL_WELCOME(const std::string &nick, const std::string &user,
                        const std::string &host) {
  return ":Welcome to the Internet Relay Network " + nick + "!" + user + "@" +
         host + " ";
}

std::string RPL_YOURHOST(const std::string &servername,
                         const std::string &version) {
  return ":Your host is " + servername + ", running version " + version;
}

std::string RPL_CREATED(const std::string &date) {
  return ":This server was created " + date;
}

std::string RPL_MYINFO(const std::string &server_name,
                       const std::string &version,
                       const std::string &user_modes,
                       const std::string &channel_modes) {
  return server_name + " " + version + " " + user_modes + " " + channel_modes;
}

std::string code_to_response(int code, const std::string &arg0,
                             const std::string &arg1, const std::string &arg2,
                             const std::string &arg3) {
  // TODO: Work on this.
  (void)code;
  (void)arg0;
  (void)arg1;
  (void)arg2;
  (void)arg3;
  return "";
}

} // namespace Response