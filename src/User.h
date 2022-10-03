/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:52:06 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 15:18:13 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __USER_H__
#define __USER_H__
#include <ctime>
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
  const Server &get_server() const;
  int get_fd() const;
  UserStatus get_status() const;
  const std::string &get_hostname() const;
  const std::string &get_hostaddr() const;
  const std::string &get_username() const;
  const std::string &get_nickname() const;
  const std::string &get_realname() const;
  const std::string &get_host() const;
  std::string get_prefix() const;
  std::time_t get_last_ping() const;

  void set_username(const std::string &username);
  void set_nickname(const std::string &nickname);
  void set_hostname(const std::string &hostname);
  void set_hostaddr(const std::string &hostaddr);
  void set_realname(const std::string &realname);
  void set_status(UserStatus status);

  void handle();
  void reply(int code, const std::string &arg0 = "",
             const std::string &arg1 = "", const std::string &arg2 = "",
             const std::string &arg3 = "", const std::string &arg4 = "",
             const std::string &arg5 = "", const std::string &arg6 = "");
  void write(const std::string &message);
  void send_to(User &user, const std::string &message);
  void broadcast(const std::string &message);

  // for pong cmd
  void set_last_ping(time_t last_ping);

private:
  Server &m_server;
  int m_fd;
  UserStatus m_status;
  std::string m_hostname;
  std::string m_hostaddr;
  std::string m_username;
  std::string m_nickname;
  time_t m_last_ping;
  std::string m_realname;
};

#endif // __USER_H__
