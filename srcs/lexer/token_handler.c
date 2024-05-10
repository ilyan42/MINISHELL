/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:49:22 by ilbendib          #+#    #+#             */
/*   Updated: 2024/05/01 11:30:16 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_special_char(char c)
{
	return (c == ';' || c == '|' || c == '<' || c == '>');
}

int	simple_quote_handler(char *buffer, t_tknlist *list)
{
	int	i;
	int	link;

	i = 1;
	link = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\'')
			break ;
		i++;
	}
	if (buffer[i] == '\0')
		return (error_handler_lexer(TKN_LIST, QUOTES_ERR_MSG));
	if (ft_isspace(buffer[i + 1]) == 0)
		link = 1;
	if (!add_node(list,
			create_node(QUOTE, ft_strndup(buffer, i + 1, TKN_LIST), link)))
		print_and_exit(MALLOC_ERR_MSG, RED, 1);
	return (i + 1);
}

int	pipe_handler(char *buffer, t_tknlist *list)
{
	if (!add_node(list, create_node(PIPE, ft_strndup(buffer, 1, TMP), 0)))
		print_and_exit(MALLOC_ERR_MSG, RED, 1);
	return (1);
}

int	file_handler(char *buffer, t_tknlist *list, t_tkntype type)
{
	int	i;

	if (type == APPEND || type == HEREDOC)
		i = 2;
	else
		i = 1;
	if (!add_node(list, create_node(type, ft_strndup(buffer, i, TKN_LIST), 1)))
		print_and_exit(MALLOC_ERR_MSG, RED, 1);
	return (i);
}

int	cmd_handler(char *buffer, t_tknlist *list)
{
	int	i;
	int	link;

	i = 0;
	link = 0;
	while (buffer[i] != '\0' && ft_isspace(buffer[i]) == 0)
	{
		if (buffer[i] == '\'' || buffer[i] == '\"'
			|| buffer[i] == '<' || buffer[i] == '>')
			break ;
		i++;
	}
	if (!(buffer[i] == '<' || buffer[i] == '>')
		&& buffer[i] != '\0' && ft_isspace(buffer[i]) == 0)
		link = 1;
	if (!add_node(list,
			create_node(WORD, ft_strndup(buffer, i, TKN_LIST), link)))
		print_and_exit(MALLOC_ERR_MSG, RED, 1);
	return (i);
}
