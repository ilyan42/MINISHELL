/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:30:07 by elanson           #+#    #+#             */
/*   Updated: 2024/05/08 13:56:04 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	waitlist(int *pid, int size)
{
	int		i;
	int		status;
	int		exit_status;

	i = 0;
	exit_status = 0;
	status = 0;
	while (i < size)
	{
		waitpid(pid[i], &status, 0);
		if (i > 0)
			kill(pid[i - 1], SIGTERM);
		if (WCOREDUMP(status) && WTERMSIG(status) == 11)
		{
			g_status = 139;
			ft_putendl_fd("Segmentation fault (core dumped)", 2);
		}
		if (WCOREDUMP(status) && WTERMSIG(status) == 3)
			ft_putendl_fd("Quit (core dumped)", 2);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		i++;
		status = 0;
	}
	return (exit_status);
}

void	redir_handler(t_redir *redir, t_cmds *cmds, t_mini *mini)
{
	int	fd_pipe[2];

	while (redir)
	{
		if (redir->type == IN)
			cmds->io[0] = open(redir->filename, O_RDONLY);
		else if (redir->type == OUT)
			cmds->io[1] = open(redir->filename, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			cmds->io[1] = open(redir->filename, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
		else if (redir->type == HEREDOC)
		{
			exec_heredoc(cmds, redir, mini, fd_pipe);
			redir = redir->next;
			continue ;
		}
		redir = redir->next;
	}
}

int	browse_list(t_mini *mini)
{
	t_cmds	*curr;
	t_redir	*redir;
	int		size;

	size = 0;
	curr = mini->cmd_list->head;
	size = get_fork_number(mini->cmd_list->head);
	if (!curr || g_status == 130)
		return (130);
	open_pipe(curr);
	while (curr)
	{
		if (curr->redir)
		{
			redir = curr->redir->head;
			redir_handler(redir, curr, mini);
		}
		curr = curr->next;
	}
	if (size > 1)
		return (pre_exec(mini->cmd_list->head, size, mini));
	return (exec_handler(mini->cmd_list->head, mini));
}
