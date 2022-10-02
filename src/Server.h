/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:33:31 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/02 15:18:48 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_H__
#define __SERVER_H__
#include <string>
#include <sys/epoll.h>

#define SERVER_MAX_CONNECTIONS 32

class Server {
public:
  Server(int port, std::string password);

  int init();
  void handle();

private:
  bool accept_new_connection();
  bool make_socket_nonblocking(int fd);
  bool add_socket_to_epoll(int fd);
  bool read_from_socket(int fd);

private:
  int m_port;
  std::string m_password;
  int m_listening_fd;

  // epoll
  int m_epoll_fd;
  epoll_event m_epoll_event;
  epoll_event m_events[SERVER_MAX_CONNECTIONS];
};

#endif // __SERVER_H__