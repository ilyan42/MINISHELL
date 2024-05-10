/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:56:21 by ilbendib          #+#    #+#             */
/*   Updated: 2024/05/03 10:28:50 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*current;

	current = s;
	if (!current)
		return (NULL);
	while (*current != '\0')
	{
		if (*current == (unsigned char)c)
			return ((char *)current);
		current++;
	}
	if (*current == (unsigned char)c)
		return ((char *)current);
	return (NULL);
}
