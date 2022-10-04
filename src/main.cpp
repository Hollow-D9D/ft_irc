/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 23:33:21 by aabajyan          #+#    #+#             */
/*   Updated: 2022/10/03 15:47:18 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Common.h"
#include "Server.h"
#include <csignal>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

static bool g_stop = false;

void handler(int) { g_stop = true; }

int main(int argc, char **argv) {

  if (argc < 3) {
    std::cout << "./ircserv [port] [password]\n";
    return 0;
  }

  try {
    Server server(std::atoi(argv[1]), std::string(argv[2]));
    server.init();
    signal(SIGINT, handler);
    signal(SIGTERM, handler);

    while (!g_stop)
      if (!server.handle())
        break;

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
