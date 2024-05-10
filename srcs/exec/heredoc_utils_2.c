/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:15:58 by ilbendib          #+#    #+#             */
/*   Updated: 2024/05/08 12:16:01 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_signals_heredoc(char *input, size_t	nb_lines, char *delim)
{
	if (!input)
	{
		if (g_status != 130)
			ft_printf_fd(2, HEREDOC_MSG, RED, (int) nb_lines, delim, RESET);
	}
}

int	readline_heredoc(char *delim, char *line, size_t *nb_lines, int fd_pipe[2])
{
	(void)fd_pipe;
	if (ft_strlen(line) > 0 && ft_strcmp(line, delim) == 0)
	{
		free(line);
		return (1);
	}
	(*nb_lines)++;
	return (0);
}

char	*get_env_value2(t_env *env, const char *var, size_t len)
{
	char	*path;

	while (env != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			path = strdup_gc(&env->value[len + 1], TMP);
			if (!path)
				print_and_exit(MALLOC_ERR_MSG, RED, 1);
			return (path);
		}
		env = env->next;
	}
	return ("");
}
