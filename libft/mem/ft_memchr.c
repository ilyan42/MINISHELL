/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:53:15 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:10:57 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*byte;
	size_t			i;

	byte = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (byte[i] == (unsigned char)c)
			return ((void *)&byte[i]);
		i++;
	}
	return (NULL);
}
