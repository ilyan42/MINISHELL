/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:49:07 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:14:18 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strndup(char *buffer, int len, t_id_gc id)
{
	char	*new;
	int		i;

	i = 0;
	while (buffer[i] && i < len)
		i++;
	new = malloc_gc((i + 1) * sizeof(char), id);
	if (!new)
		print_and_exit(MALLOC_ERR_MSG, RED, 1);
	i = 0;
	while (buffer[i] && i < len)
	{
		new[i] = buffer[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	detect_error_type(const char c)
{
	if (c == ')' || c == ';' || c == '\\')
		return (error_handler_lexer(TKN_LIST, WRONG_CHAR_ERR_MSG));
	return (0);
}
