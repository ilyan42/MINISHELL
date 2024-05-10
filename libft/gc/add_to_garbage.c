/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_garbage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:51:14 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:09:25 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*add_to_garbage(void *ptr, int id_gc)
{
	t_list	*el;

	if (id_gc < 0 || id_gc >= GARBAGE_SIZE)
		return (NULL);
	el = ft_lstnew(ptr);
	if (el == NULL)
		return (free(ptr), NULL);
	ft_lstadd_front(garbage_ptr(id_gc), el);
	return (ptr);
}
