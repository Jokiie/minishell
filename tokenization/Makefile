CC = gcc

CFLAGS = -Wall -Werror -Wextra

NAME = tokenization.a

HEADER = tokenization.h

# Files
SRCS 	= tokens_creator.c \
		characterizer.c \
		tokenizer.c \
		trimmer.c \
		var_expansion.c \
		nbr_expansion.c \
		quotes_detector.c \
		has_one_meta.c \
		has_meta.c \
		is_one_meta.c \
		is_meta.c \
		syntax_error.c \
		contains_only.c \
		
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
