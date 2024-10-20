# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/11 12:55:15 by ccodere           #+#    #+#              #
#    Updated: 2024/10/20 10:59:46 by ccodere          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = commands.a

HEADER = commands.h

# Files

SRCS 	= ft_commands.c \
		  find_executable_path.c \
		  cd.c \
		  echo.c \
		  pwd.c \
		  executable.c\
		  env.c \

OBJECTS = $(SRCS:.c=.o)

# Rules

all: $(NAME)
	
$(NAME): $(OBJECTS) $(HEADER) 
	ar -rcs $(NAME) $(OBJECTS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
