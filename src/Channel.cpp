/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 23:33:10 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/02 23:33:10 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Channel.hpp"

// Channel::Channel() : mode("n") {}

// void Channel::setName(std::string name)
//     { this->name = name; }

// std::string Channel::getName() const
//     { return this->name; }

// void Channel::setMode(std::string mode)
//     { this->mode = mode; }

// std::string Channel::getMode()
//     { return this->mode; }

// void Channel::setUserMode(User &user, std::string mode)
//     { users_mode[user.getFd()] = mode; }

// std::string Channel::getUserMode(User &user)
//     { return users_mode[user.getFd()]; }

// void Channel::addUser(User &user)
//     { users[user.getFd()] = &user; }

// void Channel::eraseUser(User &user)
//     { users.erase(users.find(user.getFd())); }

// void Channel::eraseUser(const std::string &nickname)
// {
//     std::map<int, User *>::iterator it;
//     for (it = this->users.begin(); it != this->users.end(); ++it)
//     {
//         if ((*it).second->getNickname() == nickname)
//         {
//             users.erase(it);
//             return ;
//         }
//     }
// }

// std::vector<User *> Channel::getUsers()
// {
//     std::vector<User *> v_users;

//     std::map<int, User *>::iterator it;
//     for (it = this->users.begin(); it != this->users.end(); ++it)
//         v_users.push_back((*it).second);
//     return v_users;
// }

// bool Channel::isUser(User &user)
//     { return users.find(user.getFd()) != users.end(); }

// bool Channel::inChannel(const std::string &name)
// {
//     std::map<int, User *>::iterator it;
//     for (it = this->users.begin(); it != this->users.end(); ++it)
//         if ((*it).second->getNickname() == name)
//             return true;
//     return false;
// }

// void Channel::addInvitedUser(User &user)
//     {   this->invited_users.push_back(&user); }

// bool Channel::isInvitedUser(User &user)
//     { return std::find(invited_users.begin(), invited_users.end(), &user) !=
//     invited_users.end(); }

// void Channel::eraseInvitedUser(User &user)
// {
//     std::vector<User *>::iterator it;
//     it = std::find(invited_users.begin(), invited_users.end(), &user);
//     if (it != invited_users.end())
//         invited_users.erase(it);
// }

// void Channel::broadcast(User &user, std::string message)
// {
//     std::map<int, User *>::iterator it;
//     for (it = this->users.begin(); it != this->users.end(); ++it)
//         user.sendTo(*it->second, message);
// }
