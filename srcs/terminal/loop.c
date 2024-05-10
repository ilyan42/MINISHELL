/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:48:16 by ilbendib          #+#    #+#             */
/*   Updated: 2024/05/07 11:52:43 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_loop(void)
{
	clear_garbage(TMP, free);
	clear_garbage(TKN_LIST, free);
	clear_garbage(CMDS_LIST, free);
}

static void	clear_ctrl_c(int *stdin_cpy, char **line_read)
{
	if (*line_read)
		free(*line_read);
	*line_read = NULL;
	dup2(*stdin_cpy, STDIN_FILENO);
	close(*stdin_cpy);
	clear_loop();
}

static void	sig_handler(int sigcode)
{
	if (sigcode == SIGINT)
	{
		g_status = 130;
		close(STDIN_FILENO);
		write(2, "\n", 1);
	}
	if (sigcode == SIGQUIT)
	{
		g_status = 131;
		write(2, "\b\b  \033[2D", 8);
	}
}

static void	process_shell(t_mini *mini, char *line_read, int *stdin_cpy)
{
	signal(SIGQUIT, sig_handler);
	add_history(line_read);
	mini->tknlist = lexer(line_read);
	mini->tknlist = parser(mini);
	mini->cmd_list = create_cmd_list(mini->tknlist);
	if (!mini->cmd_list)
	{
		clear_loop();
		return ;
	}
	init_all_redirs_lst(mini->tknlist, mini->cmd_list);
	init_pipes(&mini->cmd_list);
	g_status = browse_list(mini);
	dup2(*stdin_cpy, STDIN_FILENO);
	close(*stdin_cpy);
	clear_loop();
}

void	prompt_loop(t_mini *mini)
{
	int			stdin_cpy;
	char		*line_read;

	signal(SIGINT, sig_handler);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		stdin_cpy = dup(STDIN_FILENO);
		mini->last_gstatus = g_status;
		g_status = 0;
		line_read = readline(create_prompt(mini));
		if (g_status == 130)
		{
			clear_ctrl_c(&stdin_cpy, &line_read);
			continue ;
		}
		if (!line_read)
			builtin_exit(mini, NULL);
		if (line_read && *line_read)
		{
			process_shell(mini, line_read, &stdin_cpy);
		}
		close(stdin_cpy);
		free(line_read);
	}
}
