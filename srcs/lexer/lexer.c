/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:49:12 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/19 15:18:20 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	detect_type(const char c, const char c2)
{
	if (c == '\'')
		return (QUOTE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	else if (c == '|' && c2 != '|')
		return (PIPE);
	else if (c == '<' && c2 != '<')
		return (IN);
	else if (c == '>' && c2 != '>')
		return (OUT);
	else if (c == '>' && c2 == '>')
		return (APPEND);
	else if (c == '<' && c2 == '<')
		return (HEREDOC);
	return (WORD);
}

static void	handle_token(char *buffer, t_tknlist *list, t_tkntype type, int *i)
{
	if (type == DOUBLE_QUOTE)
		*i += double_quote_handler(buffer, list);
	else if (type == QUOTE)
		*i += simple_quote_handler(buffer, list);
	else if (type == PIPE)
		*i += pipe_handler(buffer, list);
	else if (type == HEREDOC || type == IN || type == OUT || type == APPEND)
		*i += file_handler(buffer, list, type);
	else if (type == WORD)
		*i += cmd_handler(buffer, list);
}

static int	is_only_space(char *buffer)
{
	size_t	i;

	i = 0;
	if (!buffer)
		return (1);
	while (buffer[i])
	{
		if (!ft_isspace(buffer[i]))
			return (0);
		i++;
	}
	return (1);
}

t_tknlist	*lexer(char *buffer)
{
	int			i;
	t_tkntype	type;
	t_tknlist	*list;

	if (!buffer || g_status != 0 || is_only_space(buffer) == 1)
		return (NULL);
	init_list(&list);
	i = 0;
	while (buffer[i])
	{
		if (!ft_isspace(buffer[i]))
		{
			if (detect_error_type(buffer[i]) == -1)
				break ;
			type = detect_type(buffer[i], buffer[i + 1]);
			handle_token(&buffer[i], list, type, &i);
			if (g_status != 0)
				break ;
		}
		else
			i++;
	}
	return (list);
}
