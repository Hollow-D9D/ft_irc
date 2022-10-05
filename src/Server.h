/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:33:31 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 18:11:57 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_H__
#define __SERVER_H__
#include <ctime>
#include <map>
#include <string>
#include <sys/select.h>
#include <vector>

#define SERVER_MAX_CONNECTIONS 32

class User;
class Command;
class Channel;

typedef void (*CommandHandlerCallback)(Command &);

class Server {
public:
  Server(int port, const std::string &password);
  ~Server();

  int init();
  bool handle();

  std::time_t get_created_at() const;
  std::string get_created_at_formatted() const;

  const std::string &get_password() const;
  int get_port() const;

  const std::map<std::string, CommandHandlerCallback> get_commands() const;

  std::map<int, User *> &get_users();
  User *get_user(const std::string &name);

  bool is_channel(std::string const &name) const;
  std::vector<Channel *> get_channels();
  Channel &get_channel(const std::string &name);
  Channel *get_channel_if_exists(const std::string &name);
  void delete_channel(Channel &chan);

  User *find_user_by_nickname(const std::string &nickname) const;

private:
  void accept_new_connection();
  bool make_socket_nonblocking(int fd);

private:
  int m_port;
  std::string m_password;
  int m_listening_fd;
  fd_set m_master_fds;
  std::time_t m_created_at;
  std::time_t m_pinged_at;
  std::map<int, User *> m_users;
  std::map<std::string, CommandHandlerCallback> m_commands;
  std::map<std::string, Channel *> m_channels;
};

#endif // __SERVER_H__
