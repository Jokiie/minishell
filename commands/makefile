CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = commands.a

HEADER = commands.h

# Files
SRCS 	= cd.c \
		echo.c \
		ft_check_cmd_path.c \
		ft_commands.c \
		pwd.c \


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
