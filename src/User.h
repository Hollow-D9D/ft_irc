/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:52:06 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/02 23:34:07 by aabajyan         ###   ########.fr       */
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

class Server;
class User {

public:
  User(int fd, const std::string &hostname, const std::string &hostaddr);
  virtual ~User();

  int get_fd() const;
  UserStatus get_status() const;
  const std::string &get_hostname() const;
  const std::string &get_hostaddr() const;
  const std::string &get_username() const;
  const std::string &get_nickname() const;

  void set_username(const std::string &username);
  void set_nickname(const std::string &nickname);

  void handle(const Server &server);
  void reply(const std::string &message);

private:
  int m_fd;
  UserStatus m_status;
  std::string m_hostname;
  std::string m_hostaddr;
  std::string m_username;
  std::string m_nickname;
};

#endif // __USER_H__