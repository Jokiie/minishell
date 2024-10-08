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

CMD = commands

#		config		#

# version = \"$(shell cat .config/version)\"

# USER = $(shell whoami)
# PWD  = \"$(shell pwd)\"

# ifeq ($(shell uname -s), Darwin)
#     BIN_DIR = \"/Users/$(USER)/Mini_bin/\"
#     L = "
# else
#     BIN_DIR = \"/home/$(USER)/Mini_bin/\"
#     L = '
# endif


# ifeq ($(shell test -d /Users/$(USER)/.brew/opt/readline; echo $$?), 0)
# 	BREW = .brew
# else ifeq ($(shell test -d /Users/$(USER)/homebrew/opt/readline; echo $$?), 0)
# 	BREW = homebrew
# endif

# TEST = $(shell test -e include/readline/libreadline.a ; echo "$$?")


# Compiler and flags
CC				=	gcc
FLAGS_SHELL		=	-D MINI_BIN=$(BIN_DIR) -D CONPILE_DIR=$(PWD) -D V_MINI=$(version)
CFLAGS			=	-Wall -Werror -Wextra -g -fno-common $(FLAGS_SHELL)
#-fsanitize=address
RM				=	rm -f

# Sources are all .c files
SRCS	=	minishell.c \
			ft_exit.c \
			ft_utils.c \
			redirection.c \
			ft_init_tokens.c \
			ft_if_is.c \

#env -i ./minishell

SRCS += $(CMD)/ft_check_cmd_path.c $(CMD)/ft_commands.c $(CMD)/cd.c $(CMD)/pwd.c \
	   $(CMD)/echo.c

OBJS	=	$(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RL_LIB) -L readline -l readline -l ncurses \
	$(RL_DIR)/$(RL_H) $(RL_DIR)/$(RL_L) -o $(NAME)

# rl:
# 	@if test $(TEST) = 1 ; then \
# 		cd readline && ./configure && make ; \
# 	else \
# 		echo readline all ready make ; sleep 1; \
# 	fi

# libft:
# 	@printf $(L)$(GRN)making libft$(WHT)\n$(L)
# 	@make -s -C $(LIBFT_DIR)
# 	@printf $(L)$(GRN)libft done$(WHT)\n$(L)

# parse:
# 	@printf $(L)$(GRN)making parsing$(WHT)\n$(L)
# 	@make -s -C parsing
# 	@printf $(L)$(GRN)parsing done$(WHT)\n$(L)

# builtin:
# 	@printf $(L)$(GRN)making builtin$(WHT)\n$(L)
# 	@make -s -C built_in
# 	@printf $(L)$(GRN)builtin done$(WHT)\n$(L)

# exe:
# 	@printf $(L)$(GRN)making execution$(WHT)\n$(L)
# 	@make -s -C $(EXECUTION_DIR)
# 	@printf $(L)$(GRN)execution done$(WHT)\n$(L)

# doc:
# 	@printf $(L)$(GRN)making doc$(WHT)\n$(L)
# 	@make -s -C $(HERE_DOC_DIR)
# 	@printf $(L)$(GRN)doc done$(WHT)\n$(L)

mem: all
	valgrind --leak-check=full --trace-children=yes --track-fds=yes --suppressions=/tmp/supp.txt ./minishell 

# readline:
# 	cd readline && ./configure && $(MAKE)

# rm_readline:
# 	cd readline && make distclean

# config:
# 	cp .config/.msrc $$HOME

# rm_config:
# 	rm $$HOME/.msrc

#https://github.com/sm222/C_tools

# Removes objects
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

ffclean: rm_readline fclean

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

.PHONY: all libft run mc readline rm_readline
