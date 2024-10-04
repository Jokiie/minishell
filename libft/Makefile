# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/22 12:04:14 by ccodere           #+#    #+#              #
#    Updated: 2024/10/02 22:11:05 by ccodere          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = libft.a

HEADER = libft.h

PRINTF_DIR = ft_printf

FPRINTF_DIR = ft_fprintf

# Files
SRCS = ft_isdigit.c ft_isalpha.c ft_isascii.c ft_isprint.c ft_strlen.c ft_bzero.c \
       ft_memset.c ft_toupper.c ft_tolower.c ft_strncmp.c ft_memmove.c ft_memcpy.c \
       ft_atoi.c ft_strlcpy.c ft_memcmp.c ft_memchr.c ft_strchr.c ft_strrchr.c \
       ft_strnstr.c ft_strlcat.c ft_strdup.c ft_calloc.c ft_substr.c ft_isalnum.c \
       ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
       ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_realloc.c \
	   ft_lstnew.c ft_lstadd_front.c ft_lstlast.c ft_lstsize.c ft_lstadd_back.c \
	   ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_str_isdigit.c ft_atol.c \
	   ft_isspace.c ft_strndup.c get_next_line.c ft_strtok.c

SRCS += $(PRINTF_DIR)/ft_printf.c $(PRINTF_DIR)/ft_itoa_base.c $(PRINTF_DIR)/ft_putbase.c \
		$(PRINTF_DIR)/ft_putbase_hex.c  $(PRINTF_DIR)/ft_putchar.c $(PRINTF_DIR)/ft_putstr.c \
		$(FPRINTF_DIR)/ft_fprintf.c $(FPRINTF_DIR)/ft_fitoa_base.c $(FPRINTF_DIR)/ft_fputbase.c \
		$(FPRINTF_DIR)/ft_fputbase_hex.c  $(FPRINTF_DIR)/ft_fputchar.c $(FPRINTF_DIR)/ft_fputstr.c

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
