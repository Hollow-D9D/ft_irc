/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 23:33:13 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/02 23:33:13 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef CHANNEL_HPP
// #define CHANNEL_HPP
// #include <iostream>
// #include <map>
// #include <vector>
// #include "User.hpp"

// class User;

// class Channel
// {
// private:
//     std::string name;
//     std::string mode;
//     std::map<int, User *> users;
//     std::map<int, std::string> users_mode;
//     std::vector<User *> invited_users;
// public:
//     Channel();

//     void setName(std::string name);
//     std::string getName() const;

//     void setMode(std::string mode);
//     std::string getMode();

//     void setUserMode(User &user, std::string mode);
//     std::string getUserMode(User &user);

//     void addUser(User &user);
//     bool isUser(User &user);
//     bool inChannel(const std::string &name);
//     void eraseUser(User &user);
//     void eraseUser(const std::string &nickname);
//     std::vector<User *> getUsers();

//     void addInvitedUser(User &user);
//     bool isInvitedUser(User &user);
//     void eraseInvitedUser(User &user);

//     void broadcast(User &user, std::string message);
// };

// #endif
