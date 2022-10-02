// #ifndef USER_HPP
// #define USER_HPP
// #include <netinet/in.h>
// #include <netdb.h>
// #include <vector>
// #include <iostream>

// class User
// {
// private:
//     int         fd;
//     std::string username;
//     std::string nickname;
//     std::string hostname;
//     std::string hostaddr;
//     std::string mode;

//     std::vector<std::string> waitingToSend;
//     void    write(std::string message);

// public:
//     User(int fd, struct sockaddr_in addr);
//     ~User();

//     void setUsername(std::string username);
//     std::string getUsername() const;

//     void setNickname(std::string nickname);
//     std::string getNickname();

//     void setMode(std::string mode);
//     std::string getMode();

//     std::string getHostname() const;
//     std::string getHostaddr() const;
//     std::string getHost() const;

//     int getFd();
//     void sendTo(User &user, std::string message);
// };




// #endif
