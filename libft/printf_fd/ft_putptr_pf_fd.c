/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_pf_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:55:59 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:11:51 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	print_ptr_addr_fd(int fd, void *ptr, size_t *count_char)
{
	unsigned long	addr;
	char			addr_str[16];
	int				i;

	if (!ptr)
	{
		ft_putstr_pf_fd(fd, "(nil)", count_char);
		return ;
	}
	addr = (unsigned long)ptr;
	ft_putstr_pf_fd(fd, "0x", count_char);
	i = 0;
	while (addr)
	{
		addr_str[i++] = "0123456789abcdef"[addr % 16];
		addr = addr / 16;
	}
	while (i > 0)
		ft_putchar_pf_fd(fd, addr_str[--i], count_char);
}
