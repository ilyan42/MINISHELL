/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:03:49 by elanson           #+#    #+#             */
/*   Updated: 2024/04/30 17:13:29 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	add_pipe_node(t_cmds **cmds)
{
	t_cmds	*node;

	node = malloc_gc(sizeof(t_cmds), CMDS_LIST);
	node->cmds = NULL;
	node->redir = NULL;
	node->io[0] = 0;
	node->io[1] = 1;
	node->next = (*cmds)->next;
	(*cmds)->next = node;
	node->is_pipe = true;
	node->is_open = false;
	node->pipe_fd[0] = 0;
	node->pipe_fd[1] = 0;
}

void	init_pipes(t_cmds_list **lst)
{
	t_cmds	*node;

	node = NULL;
	if (!(*lst) || !(*lst)->head || !lst)
		return ;
	node = (*lst)->head;
	while (node)
	{
		if (node->next && node->cmds)
		{
			add_pipe_node(&node);
			if (node->next != NULL)
				node = node->next;
		}
		node = node->next;
	}
}
