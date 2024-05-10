/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:06:30 by elanson           #+#    #+#             */
/*   Updated: 2024/05/08 14:48:50 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_heredoc(char *str, t_mini *mini)
{
	char	*var;
	char	*string;
	char	*result;
	int		i;
	int		j;

	var = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!var)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (str);
	i++;
	check_alphanum_loop(str, var, i, j);
	string = get_env_value2(mini->env, var, ft_strlen(var));
	result = replace_extend_var(str, string);
	free(var);
	return (result);
}

int	exec_heredoc(t_cmds *cmds, t_redir *redir, t_mini *mini, int *fdp)
{
	char	*line;
	size_t	nb_lines;

	start_heredoc(fdp, &line, &nb_lines);
	if (ft_strlen(line) > 0 && ft_strcmp(line, redir->filename) == 0)
		return (end_here(line, nb_lines, redir, fdp), cmds->io[0] = fdp[0], 1);
	start_heredoc2(&line, cmds, mini, nb_lines);
	if (line)
		ft_printf_fd(fdp[1], "%s\n", line);
	if (ft_strlen(line) > 0 && ft_strcmp(line, redir->filename) == 0)
		return (end_here(line, nb_lines, redir, fdp), cmds->io[0] = fdp[0], 1);
	while (line)
	{
		free(line);
		line = readline("> ");
		if (!line || readline_heredoc(redir->filename, line, &nb_lines, fdp))
			break ;
		if (!cmds->quotes && ft_strchr(line, '$'))
		{
			line = expand_heredoc(line, mini);
			handle_signals_heredoc(line, nb_lines, redir->filename);
		}
		ft_printf_fd(fdp[1], "%s\n", line);
	}
	return (end_here(line, nb_lines, redir, fdp), cmds->io[0] = fdp[0], 0);
}
