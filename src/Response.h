/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 01:59:38 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 15:47:14 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RESPONSE_H__
#define __RESPONSE_H__
#include <string>

namespace Response {
std::string RPL_WELCOME(const std::string &nick, const std::string &user,
                        const std::string &host);
std::string RPL_YOURHOST(const std::string &servername,
                         const std::string &version);
std::string RPL_CREATED(const std::string &date);
std::string RPL_MYINFO(const std::string &servername,
                       const std::string &version, const std::string &modes,
                       const std::string &channels);

std::string code_to_response(int code, const std::string &arg0,
                             const std::string &arg1, const std::string &arg2,
                             const std::string &arg3, const std::string &arg4,
                             const std::string &arg5, const std::string &arg6);
} // namespace Response

#endif // __RESPONSE_H__
