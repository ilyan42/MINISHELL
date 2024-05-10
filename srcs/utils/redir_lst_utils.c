/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:31 by ilbendib          #+#    #+#             */
/*   Updated: 2024/05/03 12:01:52 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirlst	*create_redir_list(void)
{
	t_redirlst	*list;

	list = malloc_gc(sizeof(t_redirlst), CMDS_LIST);
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

void	init_node_redir(t_redir *node, t_redirlst *list)
{
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
}

void	add_node_redirs(t_token *tkn, t_redirlst *redir_lst)
{
	t_redir	*node;

	node = malloc_gc(sizeof(t_redir), CMDS_LIST);
	if (!node)
		return ;
	node->next = NULL;
	init_node_redir(node, redir_lst);
	node->filename = tkn->content;
	node->fd = 0;
	node->is_open = false;
	node->pipe_fd[0] = 0;
	node->pipe_fd[1] = 0;
	node->type = tkn->type;
}

void	init_all_redirs_lst(t_tknlist *tkn_lst, t_cmds_list *cmd_lst)
{
	t_cmds	*cmds;
	t_token	*tkn;
	int		flag;

	flag = 0;
	if (!cmd_lst || !tkn_lst)
		return ;
	tkn = tkn_lst->head;
	cmds = cmd_lst->head;
	while (tkn)
	{
		if (tkn->type == IN || tkn->type == OUT || tkn->type == APPEND
			|| tkn->type == HEREDOC)
			handle_redir(tkn, cmds, &flag);
		if (tkn->type == PIPE)
		{
			cmds = cmds->next;
			flag = 0;
		}
		tkn = tkn->next;
	}
}
