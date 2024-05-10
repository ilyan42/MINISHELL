/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tknlist_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:42:58 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/30 18:44:56 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_in_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	if ((str[0] == '\'' && str[len - 1] == '\'')
		|| (str[0] == '\"' && str[len - 1] == '\"'))
		return (true);
	return (false);
}

bool	is_in_quotes_heredoc(t_token *tkn)
{
	if (!tkn)
		return (false);
	while (tkn->next)
	{
		if (tkn->type == HEREDOC)
		{
			if (is_in_quotes(tkn->next->content))
				return (true);
		}
		tkn = tkn->next;
	}
	return (false);
}
