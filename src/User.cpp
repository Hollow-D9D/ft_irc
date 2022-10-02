/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:53:44 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/02 17:17:08 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

User::User(int fd) : m_fd(fd), m_status(USER_STATUS_PASSWORD) {}

User::~User() {}

int User::get_fd() const { return m_fd; }

UserStatus User::get_status() const { return m_status; }

void User::handle() {

  if (m_status == USER_STATUS_DISCONNECTED)
    return;

  char buffer[BUFFER_SIZE];
  int size = recv(m_fd, buffer, BUFFER_SIZE, 0);

  if (size == -1)
    return;

  if (size == 0) {
    m_status = USER_STATUS_DISCONNECTED;
    return;
  }

  std::cout << m_fd << ": " << buffer << "\n";
}
