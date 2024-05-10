/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_gc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:51:48 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:09:41 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	max_value_size_t(size_t v1, size_t v2)
{
	if (v1 > v2)
		return (v1);
	return (v2);
}

void	*realloc_gc(void *ptr, size_t prev_size, size_t new_size, int id_gc)
{
	size_t	size;
	void	*new;

	if (new_size == 0)
		return (del_one_garbage(ptr, id_gc), NULL);
	size = (size_t) max_value_size_t(prev_size, new_size);
	new = malloc_gc(size, id_gc);
	if (ptr)
		ft_memcpy(new, ptr, size);
	del_one_garbage(ptr, id_gc);
	return (new);
}
