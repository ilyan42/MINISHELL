NAME = minishell

CC = gcc -g3
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Llibft -lft

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_MAKE = $(MAKE) -C $(LIBFT_DIR)

SRCS = 			src/main.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(LIBFT_MAKE)
	$(CC) $(CFLAGS) -Iinclude -Ilibft $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c include/minishell.h
	$(CC) $(CFLAGS) -Iinclude -Ilibft -c $< -o $@

$(LIBFT):
	$(LIBFT_MAKE)

clean:
	rm -f $(OBJS)
	$(LIBFT_MAKE) clean

fclean: clean
	rm -f $(NAME)
	$(LIBFT_MAKE) fclean

re: fclean all

.PHONY: clean fclean re all