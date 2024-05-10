/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:01:12 by elanson           #+#    #+#             */
/*   Updated: 2024/05/03 12:01:14 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_cmds *cmd, t_env *env)
{
	char	*cwd;
	char	buffer[PATH_MAX];

	cwd = get_env_value(env, "PWD", 3);
	if (cwd[0] == 0)
		cwd = getcwd(buffer, sizeof(buffer));
	if (cwd == NULL)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	else
	{
		ft_putstr_fd(cwd, cmd->io[1]);
		write(cmd->io[1], "\n", 1);
	}
	return (0);
}
