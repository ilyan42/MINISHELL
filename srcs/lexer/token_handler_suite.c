/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler_suite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:49:18 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/30 17:07:18 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	double_quote_handler(char *buffer, t_tknlist *list)
{
	int	i;
	int	link;

	i = 1;
	link = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\"')
			break ;
		i++;
	}
	if (buffer[i] == '\0')
		return (error_handler_lexer(TKN_LIST, QUOTES_ERR_MSG));
	if (ft_isspace(buffer[i + 1]) == 0)
		link = 1;
	if (!add_node(list,
			create_node(DOUBLE_QUOTE,
				ft_strndup(buffer, i + 1, TKN_LIST), link)))
		print_and_exit(MALLOC_ERR_MSG, RED, 1);
	return (i + 1);
}
