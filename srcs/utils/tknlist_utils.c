/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tknlist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:41:10 by elanson           #+#    #+#             */
/*   Updated: 2024/05/02 10:14:15 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_list(t_tknlist **list)
{
	(*list) = malloc_gc(sizeof(t_tknlist), TKN_LIST);
	if (!(*list))
		print_and_exit(MALLOC_ERR_MSG, RED, 1);
	(*list)->head = NULL;
	(*list)->tail = NULL;
}

t_token	*create_node(t_tkntype typed, char *value, int linked)
{
	t_token	*node;

	if (!value)
		return (NULL);
	node = malloc_gc(sizeof(t_token), TKN_LIST);
	if (!node)
		return (NULL);
	node->content = value;
	node->type = typed;
	node->linked = linked;
	node->index = 0;
	node->next = NULL;
	node->previous = NULL;
	node->quotes = false;
	return (node);
}

int	add_node(t_tknlist *list, t_token *node)
{
	if (!node)
		return (-1);
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		node->previous = list->tail;
		list->tail->next = node;
		list->tail = node;
	}
	return (1);
}

void	init_list_cmds(t_cmds_list **list)
{
	(*list) = malloc_gc(sizeof(t_cmds_list), CMDS_LIST);
	if (!(*list))
		print_and_exit(MALLOC_ERR_MSG, RED, 1);
	(*list)->head = NULL;
	(*list)->tail = NULL;
}

bool	cmd_is_inside_pipe(t_mini *mini)
{
	t_cmds	*node;

	node = mini->cmd_list->head;
	if (node->next)
		return (true);
	return (false);
}
