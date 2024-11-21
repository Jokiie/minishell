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

RL_DIR			=	 readline/
RL_H			=	libhistory.a
RL_L			=	libreadline.a
RL				=	$(RL_DIR)$(RL_L) $(RL_DIR)$(RL_H)

# ARCH := $(shell uname -m | sed -e s/i386/x86_64/ -e s/arm.*/arm64/)

# ifeq ($(ARCH),x86_64)
#     CC := gcc
# else
#     CC := aarch64-linux-gnu-gcc
# endif

# Compiler and flags
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -g -fno-common $(FLAGS_SHELL)
LDFLAGS			=	-lm

#-fsanitize=address
RM				=	rm -f

SRC_PATH = src/
OBJ_PATH = obj/
TMP_PATH = tmp/

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_PIPES = pipes/pipes.c \
			pipes/pipes_utils.c \
			pipes/exec_pipes.c

SRC_CMDS = commands/cd.c \
		   commands/echo.c \
		   commands/env.c \
		   commands/executable.c\
		   commands/exit.c \
		   commands/export.c \
		   commands/ft_commands.c \
		   commands/get_env.c \
		   commands/get_path.c \
		   commands/pwd.c \
		   commands/unset.c \

SRC_CMDS = commands/cd.c \
		   commands/echo.c \
		   commands/env.c \
		   commands/executable.c\
		   commands/exit.c \
		   commands/export.c \
		   commands/ft_commands.c \
		   commands/get_env.c \
		   commands/get_path.c \
		   commands/pwd.c \
		   commands/unset.c \

SRC_TOK = tokenization/tokens_creator.c \
		  tokenization/characterizer.c \
		  tokenization/tokenizer.c \
		  tokenization/trimmer.c \
		  tokenization/var_expansion.c \
		  tokenization/nbr_expansion.c \
		  tokenization/quotes_detector.c \
		  tokenization/has_one_meta.c \
		  tokenization/has_meta.c \
		  tokenization/is_one_meta.c \
		  tokenization/is_meta.c \
		  tokenization/syntax_error.c \
		  tokenization/contains_only.c \
		  tokenization/count.c \

SRC_REDIR = redirections/exec_redirections.c \
			redirections/redirection.c \
			redirections/redirection_utils.c \
			redirections/heredoc.c \
			redirections/heredoc_utils.c \
			redirections/heredoc_expander.c \
			redirections/heredoc_statics.c \
			redirections/heredoc_reset.c

SRC	=		minishell.c \
			exit_minishell.c \
			free.c \
			free_array_tab.c \
			utils.c \
			is.c \
			signal_handler.c \
			error.c \
			prompt_name.c \
			debug.c \
			$(SRC_PIPES) \
			$(SRC_REDIR) \
			$(SRC_TOK) \
			$(SRC_CMDS)

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INCS	= -I ./includes/

all: $(RL) $(LIBFT) $(OBJ_PATH) $(TMP_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/pipes
	mkdir -p $(OBJ_PATH)/commands
	mkdir -p $(OBJ_PATH)/redirections
	mkdir -p $(OBJ_PATH)/tokenization

$(TMP_PATH):
	mkdir -p $(TMP_PATH)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(RL):
	(cd $(RL_DIR) && ./configure && $(MAKE))

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RL_LIB) -L readline -l readline -l ncurses \
	$(RL) $(LDFLAGS) -o $(NAME)


# Removes objects
clean:
	# rm -f $(OBJS)
	rm -rf $(OBJ_PATH)
	rm -rf $(TMP_PATH)
	$(MAKE) -C $(LIBFT_DIR) clean
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

mem: all
#	valgrind --leak-check=full --trace-children=yes --track-fds=yes --show-leak-kinds=all --suppressions=/home/ccodere/42cursus/minishell/readline.supp ./minishell
	valgrind --leak-check=full --trace-children=yes --track-fds=yes --suppressions=/home/ccodere/42cursus/minishell/readline.supp ./minishell
#	valgrind --leak-check=full --trace-children=yes --track-fds=yes  --suppressions=/Users/$(USER)/my_cursus/minishell/readline.supp ./minishell

norm:
	norminette src/*.c $(LIBFT_DIR)/*.c commands/*.c lexing/*.c


exp:
	echo export CPPFLAGS="-I/opt/homebrew/opt/readline/include"
	echo export LDFLAGS="-L/opt/homebrew/opt/readline/lib"

.PHONY: clean fclean run mc re cp mem norm exp all libft readline rm_readline quick
