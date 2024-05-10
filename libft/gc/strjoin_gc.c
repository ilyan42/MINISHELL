/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_gc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:33:34 by elanson           #+#    #+#             */
/*   Updated: 2024/04/19 14:24:23 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*strjoin_gc(char const *s1, char const *s2, int id_gc)
{
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	dest = (char *)malloc_gc((ft_strlen(s1) \
		+ ft_strlen(s2) + 1) * sizeof(char), id_gc);
	if (!dest)
		return (NULL);
	dest[0] = '\0';
	ft_strcat(dest, s1);
	ft_strcat(dest, s2);
	return (dest);
}
