/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:35:25 by elanson           #+#    #+#             */
/*   Updated: 2024/05/01 13:02:53 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_and_exit(int exit_code)
{
	rl_clear_history();
	clear_garbage(TMP, free);
	clear_garbage(ENV, free);
	clear_garbage(TKN_LIST, free);
	clear_garbage(CMDS_LIST, free);
	exit(exit_code);
}
