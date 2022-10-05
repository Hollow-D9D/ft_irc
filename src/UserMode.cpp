/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserMode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:48:44 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 11:52:33 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserMode.h"
#include <string>

size_t UserMode::get_mode() const { return m_kind; }

bool UserMode::has_mode(UserModeKind kind) const {
  return (m_kind & kind) == kind;
}

void UserMode::set_mode(std::string mode) {
  if (mode.empty())
    return;

  size_t result = m_kind;
  UserModeChangeType change_type = USER_MODE_CHANGE_TYPE_SET;

  if (mode[0] == '+' || mode[0] == '-') {
    change_type = mode[0] == '+' ? USER_MODE_CHANGE_TYPE_ADD
                                 : USER_MODE_CHANGE_TYPE_REMOVE;
    mode = mode.substr(1);
  }

  if (mode.empty())
    return;

  for (std::string::const_iterator it = mode.begin(); it != mode.end(); ++it) {
    switch (*it) {
    case 'a':
      result |= USER_MODE_AWAY;
      break;
    case 'i':
      result |= USER_MODE_INVISIBLE;
      break;
    case 'w':
      result |= USER_MODE_WALLOPS;
      break;
    case 'r':
      result |= USER_MODE_RESTRICTED;
      break;
    case 'o':
      result |= USER_MODE_OPERATOR;
    default:
      return;
    }
  }

  switch (change_type) {
  case USER_MODE_CHANGE_TYPE_SET:
    m_kind = result;
    break;
  case USER_MODE_CHANGE_TYPE_ADD:
    m_kind |= result;
    break;
  case USER_MODE_CHANGE_TYPE_REMOVE:
    m_kind &= ~result;
    break;
  }
}

std::string UserMode::to_string() const {
  std::string result = "+";

  if (has_mode(USER_MODE_AWAY))
    result += "a";
  if (has_mode(USER_MODE_INVISIBLE))
    result += "i";
  if (has_mode(USER_MODE_WALLOPS))
    result += "w";
  if (has_mode(USER_MODE_RESTRICTED))
    result += "r";
  if (has_mode(USER_MODE_OPERATOR))
    result += "o";

  return result;
}

UserMode::UserMode() : m_kind(USER_MODE_WALLOPS) {}
