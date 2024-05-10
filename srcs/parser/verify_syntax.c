/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:48:21 by ilbendib          #+#    #+#             */
/*   Updated: 2024/05/02 15:04:36 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	verify_syntax_head(t_token *head)
{
	if (is_pipe_tkn(head->type))
	{
		ft_printf_fd(2, "%s%s `%s'%s\n", \
			RED, NEAR_TOKEN_ERR_MSG, head->content, RESET);
		return (2);
	}
	return (0);
}

static int	verify_syntax_tail(t_token *tail)
{
	if (tail->type == PIPE)
	{
		ft_printf_fd(2, "%s%s%s", RED, OPEN_PIPE_ERR_MSG, RESET);
		return (2);
	}
	if (is_redir_tkn(tail->type) || tail->type == HEREDOC)
	{
		ft_printf_fd(2, "%s%s `%s'%s\n", \
			RED, NEAR_TOKEN_ERR_MSG, "newline", RESET);
		return (2);
	}
	return (0);
}

static int	verify_syntax_body(t_token *curr)
{
	while (curr && curr->next && g_status == 0)
	{
		if (is_redir_tkn(curr->type) && curr->next->type == WORD \
			&& char_is_in_str('*', curr->next->content))
		{
			ft_printf_fd(2, "%s%s%s", RED, STAR_TOKEN_ERR_MSG, RESET);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

void	verify_syntax_tknlist(t_tknlist *lst)
{
	int	exit_status;

	exit_status = verify_syntax_head(lst->head);
	if (exit_status != 0)
	{
		g_status = exit_status;
		return ;
	}
	exit_status = verify_syntax_body(lst->head);
	if (exit_status != 0)
	{
		g_status = exit_status;
		return ;
	}
	g_status = verify_syntax_tail(lst->tail);
}
