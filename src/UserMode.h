/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserMode.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:48:40 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 11:52:34 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __USERMODE_H__
#define __USERMODE_H__
#include <string>

/*
USER MODES :
- a : away
- i : invisible
- w : wallops
- r : restricted
- o : operator
*/

enum UserModeKind {
  USER_MODE_NONE = 0,
  USER_MODE_AWAY = 1 << 0,
  USER_MODE_INVISIBLE = 1 << 1,
  USER_MODE_WALLOPS = 1 << 2,
  USER_MODE_RESTRICTED = 1 << 3,
  USER_MODE_OPERATOR = 1 << 4
};

enum UserModeChangeType {
  USER_MODE_CHANGE_TYPE_SET,
  USER_MODE_CHANGE_TYPE_ADD,
  USER_MODE_CHANGE_TYPE_REMOVE
};

class UserMode {
public:
  UserMode();

  size_t get_mode() const;
  bool has_mode(UserModeKind kind) const;
  void set_mode(std::string mode);

  std::string to_string() const;

private:
  size_t m_kind;
};

#endif // __USERMODE_H__
