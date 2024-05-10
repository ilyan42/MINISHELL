/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:54:09 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 11:54:13 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	pos_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

long long	process_number(const char *nptr, char *base, int size_base)
{
	int			i;
	int			pos;
	long long	nbr;

	i = 0;
	pos = 0;
	nbr = 0;
	while (nptr[i])
	{
		pos = pos_in_base(nptr[i], base);
		if (pos < 0)
			return (nbr);
		nbr *= size_base;
		nbr += pos;
		i++;
	}
	return (nbr);
}

int	ft_atoi_base(const char *nptr, char *base, int size_base)
{
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	if (!nptr || !base || size_base < 2)
		return (0);
	while (nptr[i] == ' ' || (nptr[i] >= 9 && (nptr[i] <= 13)))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	return ((int)(process_number(&nptr[i], base, size_base) * sign));
}
