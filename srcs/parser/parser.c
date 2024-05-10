/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:48:26 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/30 17:09:18 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_error(t_mini *mini)
{
	t_token	*tkn;

	tkn = mini->tknlist->head;
	while (tkn->next)
	{
		if (tkn->type == IN || tkn->type == OUT
			|| tkn->type == APPEND || tkn->type == HEREDOC)
		{
			if (tkn->next->type == IN || tkn->next->type == OUT
				|| tkn->next->type == APPEND || tkn->next->type == HEREDOC)
			{
				ft_printf_fd(2, "Minishell: syntax error near unexpected token\
					`%s'\n", tkn->next->content);
				g_status = 2;
				return (g_status);
			}
		}
		tkn = tkn->next;
	}
	return (0);
}

t_tknlist	*parser(t_mini *mini)
{
	if (g_status != 0 || !mini->tknlist)
	{
		clear_loop();
		return (NULL);
	}
	verify_syntax_tknlist(mini->tknlist);
	redir_error(mini);
	if (g_status != 0)
	{
		clear_loop();
		return (NULL);
	}
	reducer(mini);
	expander(mini, mini->tknlist);
	linker(mini->tknlist);
	return (mini->tknlist);
}
