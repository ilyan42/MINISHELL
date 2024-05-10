/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:51:36 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:09:36 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	**garbage_ptr(int id)
{
	static t_list	*collector[GARBAGE_SIZE];

	return (&collector[id]);
}
