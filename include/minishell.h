/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:41:21 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/26 15:34:20 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
#include <stdbool.h>

typedef enum e_type_token
{
	WORD,
	PIPE,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
	IN,
	OUT,
	APPEND,
	HEREDOC,
} 		t_type_token;

typedef struct s_token
{
	char *value;
	t_type_token type;
	size_t index;
	bool linked;
	struct s_type_token *next;
	struct s_type_token *prev;
} 		t_token;

typedef struct s_token_list
{
	struct s_type_token *head;
	struct s_type_token *tail;
}	t_token_list;

/****LEXER****/

int type(char type);
void type_manager(char *str, t_type_token type, t_token_list *list, int *pos);
int ft_ioah_manager(char *str, t_token *type, t_token_list *list);
int ft_pipe_manager(char *str,  t_token_list *list);
int ft_double_quote_manager(char *str,  t_token_list *list);
int ft_simple_quote_manager(char *str,  t_token_list *list);
int ft_create_node(t_token *token, char *value, int linked);
int ft_add_node(t_token *token, t_token *node);
t_type_token	*ft_lstlast_node(t_token *token);
int ft_strndup(char **dest, char *src, int n);
void	ft_lstclear(t_token **lst, void (*del)(void *));
void	ft_lstdelone(t_token *lst, void (*del)(void *));




#endif
