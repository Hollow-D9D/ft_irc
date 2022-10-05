/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavetyan <aavetyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:36:37 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 14:46:39 by aavetyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILITIES_H__
#define __UTILITIES_H__
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

#endif // __UTILITIES_H__
