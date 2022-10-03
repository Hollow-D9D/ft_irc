/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aavetyan <aavetyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:52:06 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 12:01:43 by aavetyan         ###   ########.fr       */
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
  User(Server &server, int fd, const std::string &hostname,
       const std::string &hostaddr);
  virtual ~User();

  Server &get_server();
  int get_fd() const;
  UserStatus get_status() const;
  const std::string &get_hostname() const;
  const std::string &get_hostaddr() const;
  const std::string &get_username() const;
  const std::string &get_nickname() const;
  const std::string &get_host() const;
  std::string get_prefix() const;

  void set_username(const std::string &username);
  void set_nickname(const std::string &nickname);
  void set_hostname(const std::string &hostname);
  void set_hostaddr(const std::string &hostaddr);
  void set_status(UserStatus status);
  
  void handle();
  void write(const std::string &message);
  void send_to(User &user, const std::string &message);
  void broadcast(const std::string &message);

private:
  Server &m_server;
  int m_fd;
  UserStatus m_status;
  std::string m_hostname;
  std::string m_hostaddr;
  std::string m_username;
  std::string m_nickname;
};

#endif // __USER_H__
