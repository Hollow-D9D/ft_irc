/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:36:37 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 11:37:32 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILITIES_H__
#define __UTILITIES_H__
#include <sstream>

namespace Utilities {
template <typename T> std::string to_string(T in) {
  std::stringstream stream;
  stream << in;
  return stream.str();
}
} // namespace Utilities

#endif // __UTILITIES_H__