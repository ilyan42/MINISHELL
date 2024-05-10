/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:15:23 by ilbendib          #+#    #+#             */
/*   Updated: 2024/05/08 14:50:05 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_alphanum_loop(char *str, char *var, int i, int j)
{
	if (str)
	{
		while ((str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= 'a' && str[i] <= 'z'))
		{
			var[j] = str[i];
			j++;
			i++;
		}
		var[j] = '\0';
	}
}

void	end_here(char *line, size_t nb_lines, t_redir *redir, int *fdp)
{
	handle_signals_heredoc(line, nb_lines, redir->filename);
	close(fdp[1]);
}

void	start_heredoc(int *fd_pipe, char **line, size_t *nb_lines)
{
	signal(SIGQUIT, SIG_IGN);
	if (pipe(fd_pipe) == -1)
		print_and_exit("Minishell: pipe error\n", RED, 1);
	*line = readline("> ");
	*nb_lines = 1;
}

void	start_heredoc2(char **line, t_cmds *cmds, t_mini *mini, size_t nb_lines)
{
	if (*line)
	{
		if (!cmds->quotes && ft_strchr(*line, '$'))
		{
			*line = expand_heredoc(*line, mini);
			handle_signals_heredoc(*line, nb_lines, cmds->cmds[0]);
		}
	}
}
