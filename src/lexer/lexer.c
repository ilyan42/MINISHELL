/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:07:10 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/25 15:00:39 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	type(char type)
{
	if (type == '<')
		return (IN);
	else if (type == '>')
		return (OUT);
	else if (type == '|')
		return (PIPE);
	else if (type == '"')
		return (DOUBLE_QUOTE);
	else if (type == '\'')
		return (SIMPLE_QUOTE);
	
}

void type_manager(t_type_token *type)
{
	if (type == IN)
		ft_in_manager(type);
	else if (type == OUT)
		ft_out_manager(type);
	else if (type == PIPE)
		ft_pipe_manager(type);
	else if (type == DOUBLE_QUOTE)
		ft_double_quote_manager(type);
	else if (type == SIMPLE_QUOTE)
		ft_simple_quote_manager(type);
}