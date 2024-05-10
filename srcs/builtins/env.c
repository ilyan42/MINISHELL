/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:01:01 by elanson           #+#    #+#             */
/*   Updated: 2024/05/03 12:01:03 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(t_env *env, t_cmds *cmd)
{
	while (env)
	{
		if (env->secret == 0 && env->value != NULL)
		{
			ft_putstr_fd(env->value, cmd->io[1]);
			write(cmd->io[1], "\n", 1);
		}
		env = env->next;
	}
	return (0);
}
