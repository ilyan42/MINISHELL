/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:30:12 by elanson           #+#    #+#             */
/*   Updated: 2024/05/07 18:22:12 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	else if (ft_strcmp(command, "cd") == 0)
		return (1);
	else if (ft_strcmp(command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(command, "env") == 0)
		return (1);
	else if (ft_strcmp(command, "export") == 0)
		return (1);
	else if (ft_strcmp(command, "unset") == 0)
		return (1);
	else if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

int	exec_handler(t_cmds *cmd, t_mini *mini)
{
	int		ret_status;
	bool	cmd_builtin;
	bool	is_pipe;

	ret_status = 0;
	cmd_builtin = is_builtin(cmd->cmds[0]);
	is_pipe = cmd_is_inside_pipe(mini);
	if (is_pipe == true && cmd_builtin == true)
		ret_status = fork_builtin(&(mini->env), cmd);
	else if (is_pipe == false && cmd_builtin == true)
		ret_status = exec_builtin(&(mini->env), cmd);
	else
		ret_status = exec_bin(mini->env, cmd);
	if (is_pipe)
		clear_garbage(ENV, free);
	clear_loop();
	return (ret_status);
}

int	exec_bin(t_env *env, t_cmds *cmd)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	exit_status = 0;
	status = 0;
	pid = fork();
	if (pid == -1)
		print_and_exit("Minishell: Fork() error.\n", RED, 1);
	if (pid == 0)
		exec_process(cmd, env);
	waitpid(pid, &status, 0);
	if (WCOREDUMP(status) && WTERMSIG(status) == 11)
	{
		g_status = 139;
		ft_putendl_fd("Segmentation fault (core dumped)", 2);
	}
	if (WCOREDUMP(status) && WTERMSIG(status) == 3)
		ft_putendl_fd("Quit (core dumped)", 2);
	exit_status = g_status;
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}
