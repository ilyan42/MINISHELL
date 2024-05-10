/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:49:38 by ilbendib          #+#    #+#             */
/*   Updated: 2024/05/07 18:17:34 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	strlen_2d(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static void	sort_env(char **tab, int len_env)
{
	int		i;
	int		flag;
	char	*tmp;

	flag = 0;
	while (tab && flag == 0)
	{
		flag = 1;
		i = 0;
		while (i < len_env - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				flag = 0;
			}
			i++;
		}
		len_env--;
	}
}

static void	print_export(char **tab, t_cmds *cmd)
{
	size_t	i;
	size_t	size_varname;

	i = 0;
	while (tab[i])
	{
		size_varname = ft_strlen_until_char(tab[i], '=');
		ft_putstr_fd("declare -x ", cmd->io[1]);
		write(cmd->io[1], tab[i], size_varname);
		if (tab[i][size_varname] == '=' && tab[i][size_varname + 1] != '\0')
		{
			write(cmd->io[1], "=\"", 2);
			write(cmd->io[1], &tab[i][size_varname + 1],
				ft_strlen(tab[i]) - size_varname - 1);
			write(cmd->io[1], "\"", 1);
		}
		write(cmd->io[1], "\n", 1);
		i++;
	}
}

void	print_sorted_env(t_env *env, t_cmds *cmd)
{
	char	**tab;
	char	*str_env;

	str_env = env_to_str(env);
	tab = ft_split(str_env, '\n');
	free(str_env);
	if (!tab)
		print_and_exit(MALLOC_ERR_MSG, RED, 1);
	sort_env(tab, strlen_2d(tab));
	print_export(tab, cmd);
	free_char2(&tab);
}
