/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:36:37 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/06 12:45:24 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILITIES_H__
#define __UTILITIES_H__
#include "Channel.hpp"
#include <sstream>
#include <string>
#include <vector>

namespace Utilities {
template <typename T> std::string to_string(T in) {
  std::stringstream stream;
  stream << in;
  return stream.str();
}

std::vector<std::string> split(std::string arg, const std::string &c);

} // namespace Utilities

std::string users_to_string(Channel &channel);

#endif // __UTILITIES_H__
