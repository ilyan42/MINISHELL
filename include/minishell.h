/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:41:21 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/25 15:03:32 by ilbendib         ###   ########.fr       */
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

typedef struct s_type_token
{
	char *value;
	t_type_token type;
	size_t index;
	bool linked;
	struct s_type_token *next;
	struct s_type_token *prev;
} 		t_type_token;

/****LEXER****/

int type(char type);
void type_manager(t_type_token *type);

#endif