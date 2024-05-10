/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:51:40 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:09:37 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	len_itoa(int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	is_negative(int *sign, int *n)
{
	if (*n < 0)
	{
		*n *= -1;
		(*sign)++;
	}
}

char	*itoa_gc(int n, int id_gc)
{
	char	*str_num;
	int		sign;
	int		len;

	if (n == 0)
		return (strdup_gc("0", id_gc));
	if (n == -2147483648)
		return (strdup_gc("-2147483648", id_gc));
	sign = 0;
	is_negative(&sign, &n);
	len = len_itoa(n);
	str_num = calloc_gc((len + 1) + sign, 1, id_gc);
	if (str_num == NULL)
		return (NULL);
	if (sign == 0)
		len--;
	while (n > 0)
	{
		str_num[len--] = (n % 10) + '0';
		n /= 10;
	}
	if (sign == 1)
		str_num[0] = '-';
	return (str_num);
}
