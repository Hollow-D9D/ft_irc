#include "User.hpp"
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

void User::write(std::string message)
    { waitingToSend.push_back(message); }

User::User(int fd, struct sockaddr_in addr)
{
    this->fd = fd;
    fcntl(fd, F_SETFL, O_NONBLOCK);
    hostaddr = inet_ntoa(addr.sin_addr);
    char hostname[NI_MAXHOST];
    if (getnameinfo((struct sockaddr *)&addr, sizeof(addr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV) != 0)
        std::cerr << "error: getnameinfo" << std::endl;
    else
        this->hostname = hostname;
}

User::~User()
    { close(fd); }

void User::setUsername(std::string username)
    { this->username = username; }

std::string User::getUsername() const
    { return this->username; }

void User::setNickname(std::string nickname)
    { this->nickname = nickname; }

std::string User::getNickname()
    { return this->nickname; }

std::string User::getHostname() const
    { return this->hostname; }

std::string User::getHostaddr() const
    { return this->hostaddr; }

void User::setMode(std::string mode)
    { this->mode = mode; }

std::string User::getMode()
    { return this->mode; }

std::string User::getHost() const
{
    if (this->hostname.size())
        return (this->hostname);
    return this->hostaddr;
}

void User::sendTo(User &user, std::string message)
    { user.write(message); }