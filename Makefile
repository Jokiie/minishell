# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/29 04:07:08 by ccodere           #+#    #+#              #
#    Updated: 2024/10/07 04:08:06 by ccodere          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = minishell

LIBFT_DIR = libft

RL_DIR = readline-8.2

RL_INCLUDES = -I$(RL_DIR)/include

RL_LIB = -L$(RL_DIR)/lib -lreadline -lhistory

LIBFT = $(LIBFT_DIR)/libft.a

CMD = commands

SRC = minishell.c ft_exit.c ft_utils.c redirection.c ft_init_tokens.c ft_if_is.c

SRC += $(CMD)/ft_check_cmd_path.c $(CMD)/ft_commands.c $(CMD)/cd.c $(CMD)/pwd.c \
	   $(CMD)/echo.c

OBJS = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RL_LIB) -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
