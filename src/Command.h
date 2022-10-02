#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <string>
#include <vector>

class Command
{
public:
    Command(std::string message);

    const std::string &get_message() const;
    const std::vector<std::string> &get_arguments() const;
    const std::string &get_prefix() const;

private:
    std::vector<std::string> m_arguments;
    std::string m_message;
    std::string m_trailer;
    std::string m_prefix;
};

#endif // __COMMAND_H__
