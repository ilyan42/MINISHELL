/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:48:36 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:14:39 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	is_link_sensitive(t_tkntype type)
{
	if (type == WORD || type == QUOTE || type == DOUBLE_QUOTE \
		|| type == APPEND || type == HEREDOC || type == IN || type == OUT)
		return (1);
	return (0);
}

void	linker(t_tknlist *tkn_lst)
{
	t_token	*curr;
	t_token	*next;
	char	*new_content;

	curr = tkn_lst->head;
	while (curr)
	{
		next = curr->next;
		if (next && curr->linked == 1 \
			&& is_link_sensitive(curr->type) && is_link_sensitive(next->type))
		{
			new_content = strjoin_gc(curr->content, next->content, TKN_LIST);
			if (!new_content)
				print_and_exit(MALLOC_ERR_MSG, RED, 1);
			curr->linked = next->linked;
			del_one_garbage(curr->content, TKN_LIST);
			pop_token_in_place(tkn_lst, next);
			curr->content = new_content;
			continue ;
		}
		curr = curr->next;
	}
}
