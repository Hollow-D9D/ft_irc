/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:33:31 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 02:27:39 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_H__
#define __SERVER_H__
#include <map>
#include <string>
#include <sys/select.h>
#include <vector>

#define SERVER_MAX_CONNECTIONS 32

class User;
class Command;

typedef void (*CommandHandlerCallback)(Command &);

class Server {
public:
  Server(int port, const std::string &password);
  ~Server();

  int init();
  void handle();

  const std::string &get_password() const;
  int get_port() const;

  const std::map<std::string, CommandHandlerCallback> get_commands() const;
  std::map<int, User *> &get_users();

private:
  void accept_new_connection();
  bool make_socket_nonblocking(int fd);

private:
  int m_port;
  std::string m_password;
  int m_listening_fd;
  fd_set m_master_fds;

  std::map<int, User *> m_users;
  std::map<std::string, CommandHandlerCallback> m_commands;
};

#endif // __SERVER_H__
