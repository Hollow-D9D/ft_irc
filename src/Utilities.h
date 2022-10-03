/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:17:12 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 21:18:05 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <string>
#include <vector>

namespace Utilities {
std::vector<std::string> split(const std::string &src,
                               const std::string delimiter);
}

#endif // __UTILITIES_H__