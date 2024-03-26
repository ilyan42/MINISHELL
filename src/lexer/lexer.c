/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:07:10 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/26 15:11:36 by ilbendib         ###   ########.fr       */
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

void type_manager(char *str, t_type_token type, t_token_list *list, int *pos)
{
	if (type == IN || type == OUT || type == APPEND || type== HEREDOC) 
		*pos += ft_ioah_manager(str, type, list);
	else if (type == PIPE)
		*pos += ft_pipe_manager(list, str);
	else if (type == DOUBLE_QUOTE)
		*pos += ft_double_quote_manager(list, str);
	else if (type == SIMPLE_QUOTE)
		*pos += ft_simple_quote_manager(list, str);
}