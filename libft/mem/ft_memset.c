/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:53:32 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:11:03 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*byte;
	size_t			i;

	i = 0;
	byte = (unsigned char *)s;
	while (i < n)
	{
		byte[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
