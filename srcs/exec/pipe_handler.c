/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:51:02 by elanson           #+#    #+#             */
/*   Updated: 2024/04/30 17:00:37 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	open_pipe(t_cmds *cmd)
{
	while (cmd)
	{
		if (cmd->next && !cmd->next->cmds)
		{
			pipe(cmd->next->pipe_fd);
			cmd->io[1] = cmd->next->pipe_fd[1];
			cmd->next->is_open = true;
			cmd->next->next->io[0] = cmd->next->pipe_fd[0];
		}
		cmd = cmd->next;
	}
}

int	get_fork_number(t_cmds *cmd)
{
	int	ret;

	ret = 0;
	while (cmd)
	{
		if (cmd->is_pipe)
			ret++;
		cmd = cmd->next;
	}
	return (ret + 1);
}
