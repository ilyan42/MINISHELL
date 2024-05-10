NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS =  srcs/lexer/error_handler.c srcs/lexer/lexer_utils.c \
		srcs/lexer/lexer.c srcs/lexer/token_handler.c \
		srcs/lexer/token_handler_suite.c \
		srcs/utils/error.c srcs/utils/print_utils.c \
		srcs/utils/tknlist_utils.c \
		srcs/utils/tknlist_utils_2.c \
		srcs/utils/tkntype_utils.c srcs/utils/cmds_lst_utils.c \
		srcs/utils/redir_lst_utils.c srcs/utils/init_pipes.c \
		srcs/utils/cmds_lst_utils2.c \
		srcs/utils/redir_lst_utils_2.c \
		srcs/utils/tknlist_utils_3.c \
		srcs/env/env_handler.c srcs/env/env_utils.c \
		srcs/env/sort_env.c \
		srcs/libft_extension/libft_extension_1.c \
		srcs/libft_extension/libft_extension_2.c \
		srcs/libft_extension/libft_extension_3.c \
		srcs/parser/parser.c srcs/parser/verify_syntax.c \
		srcs/parser/expander/expand_dollars.c \
		srcs/parser/expander/expander.c \
		srcs/parser/linker/linker.c \
		srcs/parser/reducer/reducer.c \
		srcs/terminal/loop.c \
		srcs/terminal/prompt.c \
		srcs/main.c \
		srcs/builtins/cd.c srcs/builtins/echo.c \
		srcs/builtins/env.c srcs/builtins/exit.c \
		srcs/builtins/export.c srcs/builtins/pwd.c \
		srcs/builtins/unset.c \
		srcs/exec/browse_list.c srcs/exec/exec_cmds.c \
		srcs/exec/get_path.c srcs/exec/heredoc.c \
		srcs/exec/exec_builtins.c srcs/exec/exec_bin.c \
		srcs/exec/pipe_handler.c srcs/exec/browse_list_utils.c \
		srcs/exec/heredoc_utils.c \
		srcs/exec/heredoc_utils_2.c \

OBJS = ${SRCS:.c=.o}

LIBFT_DIR = libft
LIBFT_A = libft/libft.a

all : force $(NAME)

$(LIBFT A): libft/libft.h
			$(MAKE) -C $(LIBFT_DIR) -s

$(NAME): $(OBJS) $(LIBFT_A)
			${CC} ${CFLAGS} -g3 -I include -I libft/ -o $@ $^ -Llibft -lft -lreadline

%.o: %.c include/minishell.h libft/libft.h
			${CC} ${CFLAGS} -g3 -Iinclude -Ilibft/ -c $< -o $@

force:
		make -C libft
clean:
		@$(MAKE) -C $(LIBFT_DIR) clean -s
		@$(RM) $(OBJS)

fclean: clean
		@$(MAKE) -C $(LIBFT_DIR) fclean -s
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re force
