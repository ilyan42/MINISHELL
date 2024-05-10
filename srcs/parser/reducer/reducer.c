/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reducer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:48:31 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/30 13:10:03 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	type_need_reducing(t_tkntype type)
{
	if (type == IN || type == OUT || type == APPEND \
		|| type == HEREDOC)
		return (1);
	else if (type == QUOTE)
		return (2);
	else if (type == DOUBLE_QUOTE)
		return (3);
	return (0);
}

static char	*reduce_content(t_token *tkn)
{
	char	*new_content;

	if (tkn->type == IN || tkn->type == OUT)
	{
		new_content = remove_substr(tkn->content, 0, 1 \
			+ ft_strlen_until_not(&tkn->content[1], ft_isspace));
		if (new_content[0] == '"')
			new_content = ft_strcut(new_content, 1, 1);
	}
	if (tkn->type == HEREDOC || tkn->type == APPEND)
		new_content = remove_substr(tkn->content, 0, 2 \
			+ ft_strlen_until_not(&tkn->content[2], ft_isspace));
	else if (tkn->type == DOUBLE_QUOTE \
		|| tkn->type == QUOTE)
		new_content = ft_strcut(tkn->content, 1, 1);
	return (new_content);
}

static void	set_quotes_true(t_token *tkn)
{
	if (!tkn)
		return ;
	while (tkn && tkn->type != PIPE)
	{
		tkn->quotes = true;
		tkn = tkn->next;
	}
}

void	reducer(t_mini	*mini)
{
	char	*new_content;
	t_token	*tkn;

	tkn = mini->tknlist->head;
	if (g_status != 0)
		return ;
	while (tkn)
	{
		if (is_in_quotes_heredoc(tkn))
			set_quotes_true(tkn);
		if (type_need_reducing(tkn->type))
		{
			new_content = reduce_content(tkn);
			if (!new_content)
				print_and_exit(MALLOC_ERR_MSG, RED, 1);
			add_to_garbage(new_content, TKN_LIST);
			del_one_garbage(tkn->content, TKN_LIST);
			tkn->content = new_content;
		}
		tkn = tkn->next;
	}
}
