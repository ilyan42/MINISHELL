/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:48:11 by ilbendib          #+#    #+#             */
/*   Updated: 2024/05/07 11:35:59 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_prompt(t_mini *mini)
{
	char	*home;
	char	*prompt;
	int		home_len;

	home = getenv("HOME");
	prompt = get_env_value(mini->env, "PWD", 3);
	if (!prompt)
		prompt = "Minishell";
	if (home && ft_strnstr(prompt, home, ft_strlen(home)))
	{
		home_len = ft_strlen(home);
		if (prompt[0] == '/' && prompt[1] == '/')
			home_len += 1;
		prompt[home_len - 1] = '~';
		prompt = &prompt[home_len - 1];
	}
	if (g_status == 0)
		prompt = strjoin_gc("\001\e[32;1m\002> \001\e[37m\002", prompt, TMP);
	else
		prompt = strjoin_gc("\001\e[31;1m\002> \001\e[37m\002", prompt, TMP);
	prompt = strjoin_gc(prompt, "$ ", TMP);
	if (!prompt)
		print_and_exit(MALLOC_ERR_MSG, RED, 1);
	return (prompt);
}
