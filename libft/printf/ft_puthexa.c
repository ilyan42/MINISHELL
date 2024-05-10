/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:55:25 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:11:36 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_puthexa_upper(unsigned int nbr, size_t *count_char)
{
	if (nbr > 15)
		ft_puthexa_upper(nbr / 16, count_char);
	ft_putchar_pf("0123456789ABCDEF"[nbr % 16], count_char);
}

void	ft_puthexa_lower(unsigned int nbr, size_t *count_char)
{
	if (nbr > 15)
		ft_puthexa_lower(nbr / 16, count_char);
	ft_putchar_pf("0123456789abcdef"[nbr % 16], count_char);
}
