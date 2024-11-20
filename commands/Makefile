# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matislessardgrenier <matislessardgrenie    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/11 12:55:15 by ccodere           #+#    #+#              #
#    Updated: 2024/11/20 15:01:37 by matislessar      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = commands.a

HEADER = commands.h

# Files

SRCS 	= ft_commands.c \
		  get_path.c \
		  cd.c \
		  echo.c \
		  pwd.c \
		  executable.c\
		  env.c \
		  exit.c \
		  unset.c \
		  export.c \
		  get_env.c \

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
