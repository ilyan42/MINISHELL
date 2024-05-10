/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:49:03 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:14:16 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error_handler_lexer(int id_gc, char *msg)
{
	clear_garbage(id_gc, free);
	ft_putstr_fd(msg, 2);
	g_status = 2;
	return (-1);
}
