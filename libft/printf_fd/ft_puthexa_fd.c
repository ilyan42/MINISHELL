/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:55:52 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:11:48 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_puthexa_upper_fd(int fd, unsigned int nbr, size_t *count_char)
{
	if (nbr > 15)
		ft_puthexa_upper_fd(fd, nbr / 16, count_char);
	ft_putchar_pf_fd(fd, "0123456789ABCDEF"[nbr % 16], count_char);
}

void	ft_puthexa_lower_fd(int fd, unsigned int nbr, size_t *count_char)
{
	if (nbr > 15)
		ft_puthexa_lower_fd(fd, nbr / 16, count_char);
	ft_putchar_pf_fd(fd, "0123456789abcdef"[nbr % 16], count_char);
}
