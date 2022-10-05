/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 23:33:10 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 18:34:34 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <algorithm>

Channel::Channel() : mode("n") {}

Channel::~Channel() {
  std::cout << "Channel " << this->name << " has been destroyed.\n";
}

void Channel::setName(std::string name) { this->name = name; }
std::string Channel::getName() const { return this->name; }

void Channel::setTopic(std::string topic) { this->topic = topic; }

void Channel::setMode(std::string mode) { this->mode = mode; }

std::string Channel::getMode() { return this->mode; }

std::string Channel::getTopic() { return topic; }

std::string Channel::getChannelMode() const {
  if (mode.find('p') != std::string::npos)
    return "*";
  if (mode.find('s') != std::string::npos)
    return "@";
  return "=";
}

void Channel::setUserMode(User &user, std::string mode) {
  users_mode[user.get_fd()] = mode;
}

std::string Channel::getUserMode(User &user) {
  return users_mode[user.get_fd()];
}

void Channel::addUser(User &user) { users[user.get_fd()] = &user; }

void Channel::eraseUser(User &user) {
  std::map<int, User *>::iterator it = users.find(user.get_fd());
  if (it != users.end())
    users.erase(it);
}

void Channel::eraseUser(const std::string &nickname) {
  std::map<int, User *>::iterator it;
  for (it = this->users.begin(); it != this->users.end(); ++it) {
    if ((*it).second->get_nickname() == nickname) {
      users.erase(it);
      return;
    }
  }
}

std::string Channel::getNicknames(const std::string &exclude) const {
  std::string result = "";
  for (std::map<int, User *>::const_iterator it = users.begin();
       it != users.end();) {
    User *user = it->second;
    if (user->get_nickname() == exclude) {
      ++it;
      continue;
    }
    result += user->get_nickname();
    if (++it != users.end())
      result += " ";
  }
  return result;
}

std::vector<User *> Channel::getUsers() {
  std::vector<User *> v_users;

  std::map<int, User *>::const_iterator it;
  for (it = this->users.begin(); it != this->users.end(); ++it)
    v_users.push_back((*it).second);
  return v_users;
}

bool Channel::isUser(User &user) {
  return users.find(user.get_fd()) != users.end();
}

bool Channel::inChannel(const std::string &name) {
  std::map<int, User *>::const_iterator it;
  for (it = this->users.begin(); it != this->users.end(); ++it)
    if ((*it).second->get_nickname() == name)
      return true;
  return false;
}

void Channel::addInvitedUser(User &user) {
  this->invited_users.push_back(&user);
}

bool Channel::isInvitedUser(User &user) {
  return std::find(invited_users.begin(), invited_users.end(), &user) !=
         invited_users.end();
}

void Channel::eraseInvitedUser(User &user) {
  std::vector<User *>::iterator it;
  it = std::find(invited_users.begin(), invited_users.end(), &user);
  if (it != invited_users.end())
    invited_users.erase(it);
}

void Channel::broadcast(User &user, std::string message) {
  std::map<int, User *>::iterator it;
  for (it = this->users.begin(); it != this->users.end(); ++it)
    user.send_to(*it->second, message);
}
