/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar2_endl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:58:01 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:13:34 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putchar2_endl(char **char2)
{
	size_t	i;

	i = 0;
	while (char2[i])
	{
		ft_putstr_fd(char2[i], 1);
		write(1, "\n", 1);
		i++;
	}
}
