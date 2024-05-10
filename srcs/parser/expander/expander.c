/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:48:44 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/29 15:47:55 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static bool	is_expansible(t_token *tkn)
{
	if (strcmp("$", tkn->content) == 0)
		return (false);
	if (!char_is_in_str('$', tkn->content))
		return (false);
	if (tkn->previous && tkn->previous->type == HEREDOC)
		return (false);
	if (tkn->type != WORD && tkn->type != DOUBLE_QUOTE)
		return (false);
	return (true);
}

void	expander(t_mini *mini, t_tknlist *tkn_lst)
{
	t_token	*curr;

	if (g_status != 0)
		return ;
	curr = tkn_lst->head;
	while (curr)
	{
		if (is_expansible(curr))
			curr = expand_dollar(mini, curr, tkn_lst);
		curr = curr->next;
	}
}
