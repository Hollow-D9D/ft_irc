
#include "Server.h"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

int main(int argc, char **argv) {

  if (argc < 3) {
    std::cout << "./ircserv [port] [password]\n";
    return 0;
  }

  try {
    Server server(std::atoi(argv[1]), std::string(argv[2]));
    server.init();

    for (;;)
      server.handle();

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
