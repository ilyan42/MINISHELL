/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:25:07 by ilbendib          #+#    #+#             */
/*   Updated: 2024/05/02 14:35:39 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_child_process(t_cmds *cmd, t_mini *mini)
{
	if (cmd->io[0] != STDIN_FILENO)
		dup2(cmd->io[0], STDIN_FILENO);
	if (cmd->io[1] != STDOUT_FILENO)
		dup2(cmd->io[1], STDOUT_FILENO);
	if (is_builtin(cmd->cmds[0]))
		g_status = exec_handler(cmd, mini);
	else
		exec_process(cmd, mini->env);
	exit(EXIT_SUCCESS);
}

void	close_unused_pipes(t_cmds *cmd)
{
	if (cmd->io[1] != 1)
		close(cmd->io[1]);
	if (cmd->io[0] != 0)
		close(cmd->io[0]);
}

int	*fork_processes(t_cmds *cmd, int size, t_mini *mini)
{
	int	*pid;
	int	i;

	i = 0;
	pid = calloc_gc(size, sizeof(int), CMDS_LIST);
	while (i < size && cmd)
	{
		if (cmd->is_pipe == false)
		{
			pid[i] = fork();
			if (pid[i] == 0)
				handle_child_process(cmd, mini);
			else
				close_unused_pipes(cmd);
			i++;
		}
		cmd = cmd->next;
	}
	return (pid);
}

int	pre_exec(t_cmds *cmd, int size, t_mini *mini)
{
	int	*pid;

	pid = fork_processes(cmd, size, mini);
	return (waitlist(pid, size));
}
