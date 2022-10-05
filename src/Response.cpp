/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:01:32 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/05 12:53:43 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.h"

namespace Response {
// #001
std::string RPL_WELCOME(const std::string &prefix) {
  return ":Welcome to the Internet Relay Network " + prefix;
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

// #221
std::string RPL_UMODEIS(const std::string &umodes) { return umodes; }

// #251
std::string RPL_LUSERCLIENT(const std::string &users,
                            const std::string &invisible) {
  return ":There are " + users + " users and " + invisible +
         " invisible on 1 servers";
}

// #252
std::string RPL_LUSEROP(const std::string &ops) {
  return ops + " :operator(s) online";
}

// #253
std::string RPL_LUSERUNKNOWN(const std::string &unknown) {
  return unknown + " :unknown connection(s)";
}

// #254
std::string RPL_LUSERCHANNELS(const std::string &channels) {
  return channels + " :channels formed";
}

// #255
std::string RPL_LUSERME(const std::string &users, const std::string &servers) {
  return ":I have " + users + " clients and " + servers + " servers";
}

// #301
std::string RPL_AWAY(const std::string &nick, const std::string &away_message) {
  return nick + " :" + away_message;
}

// #311
std::string RPL_WHOISUSER(const std::string &nick, const std::string &username,
                          const std::string &host,
                          const std::string &realname) {
  return nick + " " + username + " " + host + " * :" + realname;
}

// #315
std::string RPL_ENDOFWHO(const std::string &client) {
  return client + " :End of WHO list";
}

// #324
std::string RPL_CHANNELMODEIS(const std::string &channel,
                              const std::string &modestring,
                              const std::string &modes) {
  return channel + " " + modestring + " " + modes;
}

// #331
std::string RPL_NOTOPIC(const std::string &channel) {
  return channel + " :No topic is set";
}

// #332
std::string RPL_TOPIC(const std::string &channel, const std::string &topic) {
  return channel + " :" + topic;
}

// #353
std::string RPL_NAMREPLY(const std::string &channel_mode,
                         const std::string &channel, const std::string &nicks) {
  return channel_mode + " " + channel + " :" + nicks;
}

// #366
std::string RPL_ENDOFNAMES(const std::string &channel) {
  return channel + " :End of /NAMES list";
}

// #401
std::string ERR_NOSUCHNICK(const std::string &nickname) {
  return nickname + " :No such nick/channel";
}

// #402
std::string ERR_NOSUCHSERVER(const std::string &server_name) {
  return server_name + " :No such server";
}

// #403
std::string ERR_NOSUCHCHANNEL(const std::string &channel) {
  return channel + " :No such channel";
}

// #404
std::string ERR_CANNOTSENDTOCHAN(const std::string &channel) {
  return channel + " :Cannot send to channel";
}

// #405
std::string ERR_TOOMANYCHANNELS(const std::string &channel) {
  return channel + " :You have joined too many channels";
}

// #407
std::string ERR_TOOMANYTARGETS(const std::string &target,
                               const std::string error_code,
                               const std::string abort_message) {
  return target + " :" + error_code + " recipients. " + abort_message;
}

// #409
std::string ERR_NOORIGIN(void) { return ":No origin specified"; }

// #411
std::string ERR_NORECIPIENT(const std::string &command) {
  return ":No recipient given (" + command + ")";
}

// #412
std::string ERR_NOTEXTTOSEND(void) { return ":No text to send"; }

// #413
std::string ERR_NOTOPLEVEL(const std::string &mask) {
  return mask + " :No tolevel domain specified";
}

// #414
std::string ERR_WILDTOPLEVEL(const std::string &mask) {
  return mask + " :Wildcard in tolevel domain";
}

// #421
std::string ERR_UNKNOWNCOMMAND(const std::string &command) {
  return command + " :Unknown command";
}

// #431
std::string ERR_NONICKNAMEGIVEN(void) { return ":No nickname given"; }

// #432
std::string ERR_ERRONEUSNICKNAME(const std::string &nickname) {
  return nickname + " :Erroneous nickname";
}

// #433
std::string ERR_NICKNAMEINUSE(const std::string &nickname) {
  return nickname + " :Nickname is already in use";
}

// #436
std::string ERR_NICKCOLLISION(const std::string &nickname,
                              const std::string &user,
                              const std::string &host) {
  return nickname + " :Nickname collision KILL from " + user + "@" + host;
}

// #437
std::string ERR_UNAVAILRESOURCE(const std::string &nick_channel) {
  return nick_channel + " :Nick/channel is temporarily unavailable";
}

// #441
std::string ERR_USERNOTINCHANNEL(const std::string &channel,
                                 const std::string &nick) {
  return nick + " " + channel + " :They aren't on that channel";
}

// #442
std::string ERR_NOTONCHANNEL(const std::string &channel) {
  return channel + " :You're not on that channel";
}

// #451
std::string ERR_NOTREGISTERED() { return ":You have not registered"; }

// #461
std::string ERR_NEEDMOREPARAMS(const std::string &command) {
  return command + " :Not enough parameters";
}

// #462
std::string ERR_ALREADYREGISTRED(void) {
  return ":Unauthorized command (already registered)";
}

// #471
std::string ERR_CHANNELISFULL(const std::string &channel) {
  return channel + " :Cannot join channel (+l)";
}

// #473
std::string ERR_INVITEONLYCHAN(const std::string &channel) {
  return channel + " :Cannot join channel (+i)";
}

// #474
std::string ERR_BANNEDFROMCHAN(const std::string &channel) {
  return channel + " :Cannot join channel (+b)";
}

// #475
std::string ERR_BADCHANNELKEY(const std::string &channel) {
  return channel + " :Cannot join channel (+k)";
}

// #476
std::string ERR_BADCHANMASK(const std::string &channel) {
  return channel + " :Bad Channel Mask";
}

// #482
std::string ERR_CHANOPRIVSNEEDED(const std::string &channel) {
  return channel + " :You're not channel operator";
}

// #484
std::string ERR_RESTRICTED(void) { return ":Your connection is restricted!"; }

// #502
std::string ERR_USERSDONTMATCH(const std::string &client) {
  return client + " :Cant change mode for other users";
}

std::string code_to_response(int code, const std::string &arg0,
                             const std::string &arg1, const std::string &arg2,
                             const std::string &arg3, const std::string &arg4,
                             const std::string &arg5, const std::string &arg6) {
  (void)arg4;
  (void)arg5;
  (void)arg6; // TODO: Work on this.
  switch (code) {
  case 1:
    return RPL_WELCOME(arg0);

  case 2:
    return RPL_YOURHOST(arg0, arg1);

  case 3:
    return RPL_CREATED(arg0);

  case 4:
    return RPL_MYINFO(arg0, arg1, arg2, arg3);

  case 221:
    return RPL_UMODEIS(arg0);

  case 251:
    return RPL_LUSERCLIENT(arg0, arg1);

  case 252:
    return RPL_LUSEROP(arg0);

  case 253:
    return RPL_LUSERUNKNOWN(arg0);

  case 254:
    return RPL_LUSERCHANNELS(arg0);

  case 255:
    return RPL_LUSERME(arg0, arg1);

  case 301:
    return RPL_AWAY(arg0, arg1);

  case 311:
    return RPL_WHOISUSER(arg0, arg1, arg2, arg3);

  case 315:
    return RPL_ENDOFWHO(arg0);

  case 324:
    return RPL_CHANNELMODEIS(arg0, arg1, arg2);

  case 331:
    return RPL_NOTOPIC(arg0);

  case 332:
    return RPL_TOPIC(arg0, arg1);

  case 353:
    return RPL_NAMREPLY(arg0, arg1, arg2);

  case 366:
    return RPL_ENDOFNAMES(arg0);

  case 401:
    return ERR_NOSUCHNICK(arg0);

  case 402:
    return ERR_NOSUCHSERVER(arg0);

  case 403:
    return ERR_NOSUCHCHANNEL(arg0);

  case 404:
    return ERR_CANNOTSENDTOCHAN(arg0);

  case 405:
    return ERR_TOOMANYCHANNELS(arg0);

  case 407:
    return ERR_TOOMANYTARGETS(arg0, arg1, arg2);

  case 409:
    return ERR_NOORIGIN();

  case 411:
    return ERR_NORECIPIENT(arg0);

  case 412:
    return ERR_NOTEXTTOSEND();

  case 413:
    return ERR_NOTOPLEVEL(arg0);

  case 414:
    return ERR_WILDTOPLEVEL(arg0);

  case 421:
    return ERR_UNKNOWNCOMMAND(arg0);

  case 431:
    return ERR_NONICKNAMEGIVEN();

  case 432:
    return ERR_ERRONEUSNICKNAME(arg0);

  case 433:
    return ERR_NICKNAMEINUSE(arg0);

  case 436:
    return ERR_NICKCOLLISION(arg0, arg1, arg2);

  case 437:
    return ERR_UNAVAILRESOURCE(arg0);

  case 441:
    return ERR_USERNOTINCHANNEL(arg0, arg1);

  case 442:
    return ERR_NOTONCHANNEL(arg0);

  case 451:
    return ERR_NOTREGISTERED();

  case 461:
    return ERR_NEEDMOREPARAMS(arg0);

  case 462:
    return ERR_ALREADYREGISTRED();

  case 471:
    return ERR_CHANNELISFULL(arg0);

  case 473:
    return ERR_INVITEONLYCHAN(arg0);

  case 474:
    return ERR_BANNEDFROMCHAN(arg0);

  case 475:
    return ERR_BADCHANNELKEY(arg0);

  case 476:
    return ERR_BADCHANMASK(arg0);

  case 482:
    return ERR_CHANOPRIVSNEEDED(arg0);

  case 484:
    return ERR_RESTRICTED();

  case 502:
    return ERR_USERSDONTMATCH(arg0);

  default:
    return std::string();
  }
}

} // namespace Response
