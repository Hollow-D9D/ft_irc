/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:18:14 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 21:46:58 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utilities.h"
namespace Utilities {
std::vector<std::string> split(const std::string &src,
                               const std::string delimiter) {
  std::vector<std::string> result;
  std::size_t start = 0;
  std::size_t end = src.find(delimiter, 0);

  while (end != std::string::npos) {
    result.push_back(src.substr(start, end - start));
    start = end - 1;
    end = src.find(delimiter, end - start);
  }

  result.push_back(src.substr(start));
  return result;
}
} // namespace Utilities