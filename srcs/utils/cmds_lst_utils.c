/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:27:32 by elanson           #+#    #+#             */
/*   Updated: 2024/04/30 17:14:20 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	init_node(t_cmds *node, t_cmds_list **list)
{
	node->io[0] = 0;
	node->io[1] = 1;
	node->redir = NULL;
	node->next = NULL;
	node->cmds = NULL;
	node->is_open = false;
	node->pipe_fd[0] = 0;
	node->pipe_fd[1] = 0;
	node->is_pipe = false;
	node->quotes = false;
	if (!(*list)->head)
	{
		(*list)->head = node;
		(*list)->tail = node;
	}
	else
	{
		(*list)->tail->next = node;
		(*list)->tail = node;
	}
	return (1);
}

static size_t	get_cmd_size(t_token *tkn)
{
	size_t		nb_cmds;

	nb_cmds = 0;
	if (!tkn)
		return (0);
	while (tkn && tkn->type != PIPE)
	{
		if (tkn->type == WORD || tkn->type == QUOTE
			|| tkn->type == DOUBLE_QUOTE)
			nb_cmds++;
		tkn = tkn->next;
	}
	return (nb_cmds);
}

static void	fill_cmds(t_cmds *cmd, t_token *tkn, size_t size)
{
	size_t	i;
	t_token	*curr;

	i = 0;
	curr = tkn;
	while (i < size)
	{
		if (curr->type == WORD || curr->type == QUOTE
			|| curr->type == DOUBLE_QUOTE)
		{
			cmd->cmds[i] = strdup_gc(curr->content, CMDS_LIST);
			i++;
		}
		curr = curr->next;
	}
	cmd->cmds[i] = NULL;
}

static int	add_node_cmds(t_cmds_list **cmd_lst, t_token *tkn)
{
	t_cmds	*cmd;
	size_t	size;

	cmd = malloc_gc(sizeof(t_cmds), CMDS_LIST);
	size = get_cmd_size(tkn);
	if (!init_node(cmd, cmd_lst))
		return (-1);
	cmd->cmds = (char **)malloc_gc((size + 1) * sizeof(char *), CMDS_LIST);
	fill_cmds(cmd, tkn, size);
	cmd->quotes = tkn->quotes;
	return (0);
}

t_cmds_list	*create_cmd_list(t_tknlist *tkn_lst)
{
	t_token		*curr;
	t_cmds_list	*cmd_lst;

	if (!tkn_lst)
		return (NULL);
	init_list_cmds(&cmd_lst);
	curr = tkn_lst->head;
	add_node_cmds(&cmd_lst, curr);
	while (curr)
	{
		if (curr->type == PIPE)
			add_node_cmds(&cmd_lst, curr->next);
		curr = curr->next;
	}
	return (cmd_lst);
}
