#include "Utilities.h"

std::vector<std::string> Utilities::split(std::string arg,
                                          const std::string &c) {
  std::vector<std::string> channels;
  size_t pos;
  while ((pos = arg.find(c)) != std::string::npos) {
    channels.push_back(arg.substr(0, pos));
    arg.erase(0, pos + 1);
  }
  channels.push_back(arg);
  return channels;
}