/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:10:40 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/26 15:57:57 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_ioah_manager(char *str, t_token *type, t_token_list *list)
{
	int i;
	if (type == APPEND)
		i = 1;
	else if (type == HEREDOC)
		i = 2;
	else
		i = 0;
	if (!ft_add_node(list, ft_create_node(type, ft_strndup(str, i, 1), 1)))
		return ;
}

int ft_pipe_manager(t_token_list *list, char *str)
{
	if (!ft_add_node(list, ft_create_node(PIPE, ft_strndup(str, 0, 1), 1)))
		return ;
}

int ft_simple_quote_manager(t_token_list *list, char *str)
{
	int i = 1;
	int double_simple_quote = 0;
	while (str[i] && str[i] != '\'')
	{
		if (str[i] == '\'')
			double_simple_quote = 1;
		i++;
	}
	if (double_simple_quote)
	{
		if (!ft_add_node(list, ft_create_node(SIMPLE_QUOTE, ft_strndup(str, i, 1), 1)))
			return ;
	}
	else
		ft_lstclear(list, free);
}

int ft_double_quote_manager(t_token_list *list, char *str)
{
	int i = 1;
	int double_double_quote = 0;
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '"')
			double_double_quote = 1;
		i++;
	}
	if (double_double_quote)
	{
		if (!ft_add_node(list, ft_create_node(DOUBLE_QUOTE, ft_strndup(str, i, 1), 1)))
			return ;
	}
	else
		ft_lstclear(list, free);
}