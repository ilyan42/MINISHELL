/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_char2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:57:58 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:13:32 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_char2(char ***a_char2)
{
	size_t	i;
	char	**char2;

	i = 0;
	char2 = *a_char2;
	while (char2[i])
	{
		free(char2[i]);
		char2[i] = NULL;
		i++;
	}
	free(char2);
}
