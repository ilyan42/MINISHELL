/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkntype_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:47:40 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 14:01:46 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_cmd_tkn(t_tkntype tkntype)
{
	if (tkntype == WORD || tkntype == QUOTE || tkntype == DOUBLE_QUOTE)
		return (1);
	return (0);
}

int	is_redir_tkn(t_tkntype tkntype)
{
	if (tkntype == IN || tkntype == OUT || tkntype == APPEND)
		return (1);
	return (0);
}

int	is_pipe_tkn(t_tkntype tkntype)
{
	if (tkntype == PIPE)
		return (1);
	return (0);
}
