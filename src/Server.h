/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:33:31 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/02 23:33:52 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_H__
#define __SERVER_H__
#include <string>
#include <sys/select.h>
#include <vector>

#define SERVER_MAX_CONNECTIONS 32

class User;
class Server {
public:
  Server(int port, std::string password);
  ~Server();

  int init();
  void handle();

  const std::string &get_password() const;
  int get_port() const;

private:
  void accept_new_connection();
  bool make_socket_nonblocking(int fd);

  User *find_user_by_fd(int fd);

private:
  int m_port;
  std::string m_password;
  int m_listening_fd;
  fd_set m_master_fds;
  std::vector<User *> m_users;
};

#endif // __SERVER_H__
