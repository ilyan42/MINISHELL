/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:37:14 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/30 18:45:13 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_redir_list(t_cmds *cmds, t_token *tkn)
{
	cmds->redir = create_redir_list();
	add_node_redirs(tkn, cmds->redir);
}

void	handle_redir(t_token *tkn, t_cmds *cmds, int *flag)
{
	if (*flag == 0)
	{
		init_redir_list(cmds, tkn);
		*flag = 1;
	}
	else
		add_node_redirs(tkn, cmds->redir);
}
