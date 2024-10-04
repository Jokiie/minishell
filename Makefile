# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/29 04:07:08 by ccodere           #+#    #+#              #
#    Updated: 2024/10/04 13:09:42 by ccodere          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = minishell

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = source

SRCS = $(SRC_DIR)/minishell.c $(SRC_DIR)/ft_exit.c $(SRC_DIR)/ft_utils.c \
	   $(SRC_DIR)/redirection.c $(SRC_DIR)/ft_parser.c $(SRC_DIR)/ft_if_is.c \
	   $(SRC_DIR)/commands/ft_check_cmd_path.c $(SRC_DIR)/commands/ft_commands.c \
	   $(SRC_DIR)/commands/cd.c $(SRC_DIR)/commands/pwd.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/$(OBJS)
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
