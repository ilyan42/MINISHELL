/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:53:24 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:11:00 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src,	size_t n)
{
	unsigned char			*destination;
	const unsigned char		*source;
	size_t					n_bytes;

	if (dest == NULL && src == NULL)
		return (NULL);
	destination = (unsigned char *)dest;
	source = (const unsigned char *)src;
	n_bytes = 0;
	while (n_bytes < n)
	{
		destination[n_bytes] = source[n_bytes];
		n_bytes++;
	}
	return (dest);
}
