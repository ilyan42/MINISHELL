/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_lst_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:07:32 by elanson           #+#    #+#             */
/*   Updated: 2024/04/30 17:13:57 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	get_cmd_lst_length(t_cmds *cmd)
{
	size_t	ret;
	t_cmds	*curr;

	curr = cmd;
	ret = 0;
	while (curr)
	{
		curr = curr->next;
		ret++;
	}
	return (ret);
}
