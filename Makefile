# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabajyan <arsen.abajyan@pm.me>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/24 20:41:09 by aabajyan          #+#    #+#              #
#    Updated: 2022/10/05 12:00:09 by aabajyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ircserv
SRCS = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=objs/%.o)
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -Isrc

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

objs/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

debug: CXXFLAGS += -g -O0 -DDEBUG
debug: all

leaks: debug
	valgrind --leak-check=full ./$(NAME) 6667 password

.PHONY: all clean fclean re debug leaks
