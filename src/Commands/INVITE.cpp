#include "../Channel.hpp"
#include "../Command.h"
#include "../Server.h"
#include "../User.h"

void INVITE(Command &cmd) {
  // Numeric error responses
  if (cmd.get_arguments().size() < 2)
    return cmd.get_sender().reply(461, "INVITE");

  if (cmd.get_server().get_user(cmd.get_arguments()[0]) == NULL)
    return cmd.get_sender().reply(401, cmd.get_arguments()[1]);

    if (cmd.get_server().get_channel(cmd.get_arguments()[0]).inChannel(cmd.get_arguments()[1]))
        cmd.get_sender().reply(443, cmd.get_arguments()[0], cmd.get_arguments()[1]);
    
    // Implementation
    if (cmd.get_server().is_channel(cmd.get_arguments()[1]))
    {
        Channel &channel = cmd.get_server().get_channel(cmd.get_arguments()[1]);
        if (channel.getChannelMode().find('i') != std::string::npos &&
            channel.getUserMode(cmd.get_sender()).find('o') != std::string::npos &&
            !cmd.get_sender().get_user_mode().has_mode(USER_MODE_OPERATOR))
        {
            cmd.get_sender().reply(482, cmd.get_arguments()[1]);
            return;
        }
        else if (!channel.inChannel(cmd.get_sender().get_nickname()))
        {
            cmd.get_sender().reply(442, cmd.get_arguments()[1]);
            return;
        }
        channel.addInvitedUser(*(cmd.get_server().get_user(cmd.get_arguments()[0])));
    }
    cmd.get_sender().send_to(*(cmd.get_server().get_user(cmd.get_arguments()[0])), "INVITE" + cmd.get_arguments()[0] + " " + cmd.get_arguments()[1]);
    cmd.get_sender().reply(341, cmd.get_arguments()[0], cmd.get_arguments()[1]);
    if (cmd.get_server().get_user(cmd.get_arguments()[0])->get_user_mode().has_mode(USER_MODE_AWAY))
        cmd.get_sender().reply(301, cmd.get_arguments()[0], AWAY_MESSAGE);

}
