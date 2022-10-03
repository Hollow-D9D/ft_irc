/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:01:32 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 11:31:57 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.h"

namespace Response {
// #001
std::string RPL_WELCOME(const std::string &nick, const std::string &user,
                        const std::string &host) {
  return ":Welcome to the Internet Relay Network " + nick + "!" + user + "@" +
         host + " ";
}
// #002
std::string RPL_YOURHOST(const std::string &servername,
                         const std::string &version) {
  return ":Your host is " + servername + ", running version " + version;
}
// #003
std::string RPL_CREATED(const std::string &date) {
  return ":This server was created " + date;
}
// #004
std::string RPL_MYINFO(const std::string &server_name,
                       const std::string &version,
                       const std::string &user_modes,
                       const std::string &channel_modes) {
  return server_name + " " + version + " " + user_modes + " " + channel_modes;
}
// #301
std::string RPL_AWAY(const std::string &nick,
                      const std::string &away_message){
  return nick + " :" + away_message;
}
// #331
std::string RPL_NOTOPIC(const std::string &channel) { return channel + " :No topic is set";}
// #332
std::string RPL_TOPIC(const std::string &channel,
                      const std::string &topic){
  return channel + " :" + topic;
}
// #401
std::string ERR_NOSUCHNICK(const std::string &nickname) { return nickname + " :No such nick/channel"; }
// #402
std::string ERR_NOSUCHSERVER(const std::string &server_name) { return server_name + ":No such server"; }
// #403
std::string ERR_NOSUCHCHANNEL(const std::string &channel) { return channel + " :No such channel";}
// #404
std::string ERR_CANNOTSENDTOCHAN(const std::string &channel) { return channel + " :Cannot send to channel";}
// #405
std::string ERR_TOOMANYCHANNELS(const std::string &channel) { return channel + " :You have joined too many channels";}
// #407
std::string ERR_TOOMANYTARGETS(const std::string &target,
                               const std::string error_code,
                               const std::string abort_message)
{ return target + " :" + error_code + " recipients. " + abort_message;}
// #409
std::string ERR_NOORIGIN(void) { return ":No origin specified";}
// #411
std::string ERR_NORECIPIENT(const std::string &command){ return ":No recipient given (" + command + ")"; }
// #412
std::string ERR_NOTEXTTOSEND(void) { return ":No text to send";}
// #413
std::string ERR_NOTOPLEVEL(const std::string &mask) { return mask + " :No tolevel domain specified";}
// #414
std::string ERR_WILDTOPLEVEL(const std::string &mask) { return mask + " :Wildcard in tolevel domain";}
// #421
std::string ERR_UNKNOWNCOMMAND(const std::string &command){ return command + " :Unknown command"; }
// #431
std::string ERR_NONICKNAMEGIVEN(void) { return ":No nickname given";}
// #432
std::string ERR_ERRONEUSNICKNAME(const std::string &nickname) { return nickname + " :Erroneous nickname"; }
// #433
std::string ERR_NICKNAMEINUSE(const std::string &nickname) { return nickname + " :Nickname is already in use";}
// #436
std::string ERR_NICKCOLLISION(const std::string &nickname,
                              const std::string &user,
                              const std::string &host){ 
  return nickname + " :Nickname collision KILL from " + user + "@" + host;
}
// #437
std::string ERR_UNAVAILRESOURCE(const std::string &nick_channel,
                                const bool &is_channel){
return is_channel ? nick_channel + " :channel is temporarily unavailable" : nick_channel + " :Nick is temporarily unavailable";
}
// #441
std::string ERR_USERNOTINCHANNEL(const std::string &channel,
                                 const std::string &nick) {
return nick + " " + channel + " :They aren't on that channel";
}
// #442
std::string ERR_NOTONCHANNEL(const std::string &channel) { return channel + " :You're not on that channel";}
// #461
std::string ERR_NEEDMOREPARAMS(const std::string &command){ return command + " :Not enough parameters"; }
// #462
std::string ERR_ALREADYREGISTRED(void) { return ":Unauthorized command (already registered)";}
// #471
std::string ERR_CHANNELISFULL(const std::string &channel) { return channel + " :Cannot join channel (+l)";}
// #473
std::string ERR_INVITEONLYCHAN(const std::string &channel) { return channel + " :Cannot join channel (+i)";}
// #474
std::string ERR_BANNEDFROMCHAN(const std::string &channel) { return channel + " :Cannot join channel (+b)";}
// #475
std::string ERR_BADCHANNELKEY(const std::string &channel) { return channel + " :Cannot join channel (+k)";}
// #476
std::string ERR_BADCHANMASK(const std::string &channel) { return channel + " :Bad Channel Mask";}
// #482
std::string ERR_CHANOPRIVSNEEDED(const std::string &channel) { return channel + " :You're not channel operator";}
// #484
std::string ERR_RESTRICTED(void) { return ":Your connection is restricted!";}



std::string code_to_response(int code, const std::string &arg0,
                             const std::string &arg1, const std::string &arg2,
                             const std::string &arg3, const std::string &arg4,
                             const std::string &arg5, const std::string &arg6) {
  // TODO: Work on this.
  (void)code;
  (void)arg0;
  (void)arg1;
  (void)arg2;
  (void)arg3;
  (void)arg4;
  (void)arg5;
  (void)arg6;
  return "";
}

} // namespace Response