RED				=	\x1B[31m
GRN				=	\x1B[32m
YEL				=	\x1B[33m
BLU				=	\x1B[34m
MAG				=	\x1B[35m
CYN				=	\x1B[36m
WHT				=	\x1B[37m
RESET			=	\x1B[0m
CLE 			=	\e[1;1H\e[2J

NAME			=	minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

RL_DIR			=	readline/
RL_H			=	libhistory.a
RL_L			=	libreadline.a
RL				=	$(RL_DIR)$(RL_H) $(RL_DIR)$(RL_L)
CMD = commands

ARCH := $(shell uname -m | sed -e s/i386/x86_64/ -e s/arm.*/arm64/)

ifeq ($(ARCH),x86_64)
    CC := gcc
else
    CC := aarch64-linux-gnu-gcc
endif

# Compiler and flags
#CC				=	gcc
FLAGS_SHELL		=	-D MINI_BIN=$(BIN_DIR) -D CONPILE_DIR=$(PWD) -D V_MINI=$(version)
CFLAGS			=	-Wall -Werror -Wextra -g -fno-common $(FLAGS_SHELL)
LDFLAGS := -lm
#-fsanitize=address
RM				=	rm -f

# Sources are all .c files
SRCS	=	minishell.c \
			ft_exit.c \
			ft_utils.c \
			redirection.c \
			ft_init_tokens.c \
			ft_if_is.c \


SRCS += $(CMD)/ft_check_cmd_path.c $(CMD)/ft_commands.c $(CMD)/cd.c $(CMD)/pwd.c \
	   $(CMD)/echo.c

OBJS	=	$(SRCS:.c=.o)

all: $(RL) $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(RL):
	( cd $(RL_DIR) && ./configure && $(MAKE))

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RL_LIB) -L readline -l readline -l ncurses \
	$(RL) $(LDFLAGS) -o $(NAME)

mem: all
#	valgrind --leak-check=full --trace-children=yes --track-fds=yes --suppressions=/tmp/supp.txt ./minishell 
	valgrind --leak-check=full --trace-children=yes --track-fds=yes ./minishell 

# Removes objects
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(RL_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(RL_DIR) distclean

run: all
	@./$(NAME)

mc: all clean

re: fclean all

cp:
	cp supp.txt /tmp

norm:
	norminette *.c parsing here_doc/ signal/ execution include built_in lib

exp:
	echo export CPPFLAGS="-I/opt/homebrew/opt/readline/include"
	echo export LDFLAGS="-L/opt/homebrew/opt/readline/lib"

.PHONY: all libft run mc re cp readline rm_readline
