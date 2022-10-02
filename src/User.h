/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:52:06 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/02 16:22:30 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __USER_H__
#define __USER_H__
#include <string>

enum UserStatus {
  USER_STATUS_PASSWORD,
  USER_STATUS_REGISTER,
  USER_STATUS_ONLINE,
  USER_STATUS_DISCONNECTED
};

#define BUFFER_SIZE 4096

class User {

public:
  User(int fd);
  virtual ~User();

  int get_fd() const;
  UserStatus get_status() const;

  void handle();

private:
  int m_fd;
  UserStatus m_status;
};

#endif // __USER_H__