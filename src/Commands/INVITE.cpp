#include "../Channel.hpp"
#include "../Command.h"
#include "../Server.h"
#include "../User.h"

void INVITE(Command &cmd) {

  const std::vector<std::string> &arguments = cmd.get_arguments();
  User &sender = cmd.get_sender();
  Server &server = cmd.get_server();

  // Numeric error responses
  if (arguments.size() < 2)
    return sender.reply(461, "INVITE");

  if (server.get_user(arguments[0]) == NULL)
    return sender.reply(401, arguments[1]);

  if (server.get_channel(arguments[0]).inChannel(arguments[1]))
    sender.reply(443, arguments[0], arguments[1]);

  // Implementation
  if (server.is_channel(arguments[1])) {
    Channel &channel = server.get_channel(arguments[1]);
    if (channel.getChannelMode().find('i') != std::string::npos &&
        channel.getUserMode(sender).find('o') != std::string::npos &&
        !sender.get_user_mode().has_mode(USER_MODE_OPERATOR)) {
      sender.reply(482, arguments[1]);
      return;
    } else if (!channel.inChannel(sender.get_nickname())) {
      sender.reply(442, arguments[1]);
      return;
    }
    channel.addInvitedUser(*(server.get_user(arguments[0])));
  }
  sender.send_to(*(server.get_user(arguments[0])),
                 "INVITE " + arguments[0] + " " + arguments[1]);
  sender.reply(341, arguments[0], arguments[1]);
  if (server.get_user(arguments[0])->get_user_mode().has_mode(USER_MODE_AWAY))
    sender.reply(301, arguments[0], AWAY_MESSAGE);
}
