# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 17:21:27 by yez-zain          #+#    #+#              #
#    Updated: 2021/11/18 17:39:13 by yez-zain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = computor
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror

SRC = main.cpp computor.cpp utilities.cpp expression.cpp token.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) -c $(SRC)
	@$(CXX) -o $(NAME) $(OBJ)
clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
