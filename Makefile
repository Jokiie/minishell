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
LDFLAGS			=	-lm -lreadline

#-fsanitize=address
RM				=	rm -f

SRC_PATH = src/
OBJ_PATH = obj/

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CMDS_DIR = commands
CMDS = $(CMDS_DIR)/commands.a

LEX_DIR = lexing
LEX = $(LEX_DIR)/lexing.a

# Sources are all .c files
SRC	=		minishell.c \
			ft_exit.c \
			ft_free.c \
			ft_utils.c \
			ft_if_is.c \
			ft_signal_handler.c \
			ft_error.c \
			ft_display.c \
			pipes.c \


SRCS += $(CMD_DIR)/ft_check_cmd_path.c $(CMD_DIR)/ft_commands.c $(CMD_DIR)/cd.c \
		$(CMD_DIR)/pwd.c $(CMD_DIR)/echo.c

SRCS += $(LEX_DIR)/characterizer.c $(LEX_DIR)/tokenizer.c $(LEX_DIR)/trimmer.c \
		$(LEX_DIR)/redirection.c $(LEX_DIR)/var_expansion.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INCS	= -I ./includes/

all: $(RL) $(LIBFT) $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(CMDS):
	$(MAKE) -C $(CMDS_DIR) all

$(LEX):
	$(MAKE) -C $(LEX_DIR) all

$(RL):
	(cd $(RL_DIR) && ./configure && $(MAKE))

$(NAME): $(OBJS) $(CMDS) $(LEX)
	$(CC) $(CFLAGS) $(OBJS) $(CMDS) $(LEX) $(LIBFT) $(RL_LIB) -L readline -l readline -l ncurses \
	$(RL) $(LDFLAGS) -o $(NAME)


# Removes objects
clean:
	# rm -f $(OBJS)
	rm -rf $(OBJ_PATH)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(CMDS_DIR) clean
	$(MAKE) -C $(LEX_DIR) clean
	$(MAKE) -C $(RL_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(CMDS_DIR) fclean
	$(MAKE) -C $(LEX_DIR) fclean
	$(MAKE) -C $(RL_DIR) distclean

run: all
	@./$(NAME)

mc: all clean

re: fclean all

quick:
	$(MAKE) -C $(LIBFT_DIR) all
	$(MAKE) -C $(CMDS_DIR) all
	$(MAKE) -C $(LEX_DIR) all

cp:
	cp supp.txt /tmp

mem: all
#	valgrind --leak-check=full --trace-children=yes --track-fds=yes --show-leak-kinds=all --suppressions=/home/ccodere/42cursus/minishell/readline.supp ./minishell
#	valgrind --leak-check=full --trace-children=yes --track-fds=yes --suppressions=/home/ccodere/42cursus/minishell/readline.supp ./minishell
	valgrind --leak-check=full --trace-children=yes --track-fds=yes  --suppressions=/Users/$(USER)/my_cursus/minishell/readline.supp ./minishell

norm:
	norminette src/*.c $(LIBFT_DIR)/*.c commands/*.c lexing/*.c


exp:
	echo export CPPFLAGS="-I/opt/homebrew/opt/readline/include"
	echo export LDFLAGS="-L/opt/homebrew/opt/readline/lib"

.PHONY: clean fclean run mc re cp mem norm exp all libft readline rm_readline quick
