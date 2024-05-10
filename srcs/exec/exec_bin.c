/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:44:09 by elanson           #+#    #+#             */
/*   Updated: 2024/05/03 10:34:27 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**env_to_char2(t_env *env)
{
	size_t	len;
	size_t	i;
	char	**env_2d;
	t_env	*tmp;

	tmp = env;
	i = 0;
	len = strlen_env(env);
	env_2d = (char **)malloc((len + 1) * sizeof(char *));
	if (!env_2d)
		print_and_exit(MALLOC_ERR_MSG, RED, 1);
	add_to_garbage(env_2d, TMP);
	tmp = env;
	while (i < len)
	{
		env_2d[i] = strdup_gc(tmp->value, TMP);
		if (!env_2d[i])
			print_and_exit(MALLOC_ERR_MSG, RED, 1);
		i++;
		tmp = tmp->next;
	}
	env_2d[i] = NULL;
	return (env_2d);
}

static char	*path_handler(t_cmds *cmds, t_env *env)
{
	char	*cmdpath;
	char	*cmd;

	cmd = cmds->cmds[0];
	cmdpath = NULL;
	if (!cmd)
		free_and_exit(1);
	else if (cmd && (cmd[0] == '.' || cmd[0] == '\\' || cmd[0] == '/'))
	{
		if (ft_strcmp(cmd, ".") == 0 && !cmds->cmds[1])
			print_path_error(cmd, 2, 5);
		else if (ft_strcmp(cmd, "..") == 0)
			print_path_error(cmd, 127, 1);
		else
			cmdpath = cmd;
	}
	else if (cmd && cmd[0] != '\0')
		cmdpath = get_cmd_path(cmd, env);
	check_path(cmd, cmdpath);
	return (cmdpath);
}

void	execute_fd(t_cmds *cmd)
{
	if (dup2(cmd->io[0], STDIN_FILENO) == -1)
		print_and_exit(strerror(errno), RED, 1);
	if (dup2(cmd->io[1], STDOUT_FILENO) == -1)
		print_and_exit(strerror(errno), RED, 1);
	if (cmd->io[1] != 1)
		close(cmd->io[1]);
	if (cmd->io[0] != 0)
		close(cmd->io[0]);
}

void	exec_process(t_cmds *cmd, t_env *env)
{
	char		*cmdpath;
	struct stat	stats;
	int			i;

	execute_fd(cmd);
	i = 3;
	cmdpath = path_handler(cmd, env);
	if (lstat(cmdpath, &stats) != -1)
	{
		if ((stats.st_mode & S_IXUSR) && (stats.st_mode & S_IFREG))
		{
			while (i < 32)
				close(i++);
			execve(cmdpath, cmd->cmds, env_to_char2(env));
			print_and_exit(strerror(errno), RED, 1);
		}
		else
			print_path_error(cmd->cmds[0], 126, 2);
	}
	else
		print_path_error(cmd->cmds[0], 127, 3);
}
