/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 01:59:38 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 02:10:34 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RESPONSE_H__
#define __RESPONSE_H__
#include <string>

namespace Response {
std::string welcome(const std::string &nick, const std::string &user,
                    const std::string &host);
std::string your_host(const std::string &servername,
                      const std::string &version);
std::string created(const std::string &date);
std::string my_info(const std::string &servername, const std::string &version,
                    const std::string &modes, const std::string &channels);
} // namespace Response

#endif // __RESPONSE_H__