/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:39:00 by elanson           #+#    #+#             */
/*   Updated: 2024/05/07 11:48:31 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_builtin( t_env **envt, t_cmds *cmd)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd->cmds[0], "echo") == 0)
		status = echo(cmd->cmds, cmd);
	else if (ft_strcmp(cmd->cmds[0], "cd") == 0)
		status = cd(cmd->cmds, envt);
	else if (ft_strcmp(cmd->cmds[0], "pwd") == 0)
		status = ft_pwd(cmd, *envt);
	else if (ft_strcmp(cmd->cmds[0], "env") == 0)
		env(*envt, cmd);
	else if (ft_strcmp(cmd->cmds[0], "export") == 0)
		status = ft_export(cmd->cmds, envt, cmd);
	else if (ft_strcmp(cmd->cmds[0], "unset") == 0)
		status = unset(cmd->cmds, envt);
	else if (ft_strcmp(cmd->cmds[0], "exit") == 0)
		status = builtin_exit(singleton_mini(NULL), cmd->cmds);
	return (status);
}

int	fork_builtin(t_env **env, t_cmds *cmd)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	exit_status = 0;
	pid = fork();
	status = 0;
	if (pid == -1)
		print_and_exit("Minishell: Fork() error.\n", RED, 1);
	if (pid == 0)
	{
		status = exec_builtin(env, cmd);
		free_and_exit(status);
	}
	waitpid(pid, &status, 0);
	if (WCOREDUMP(status) && WTERMSIG(status) == 11)
	{
		g_status = 139;
		ft_putendl_fd("Segmentation fault (core dumped)", 2);
	}
	if (WCOREDUMP(status) && WTERMSIG(status) == 3)
		ft_putendl_fd("Quit (core dumped)", 2);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}
