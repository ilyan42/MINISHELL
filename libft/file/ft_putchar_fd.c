/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:49:50 by ilbendib          #+#    #+#             */
/*   Updated: 2024/05/08 12:19:09 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	attach_suffix(char *str, char *result, int k)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	while (str[i])
	{
		result[k] = str[i];
		k++;
		i++;
	}
	result[k] = '\0';
}

char	*extend_var(char *var, char *result, int i, char *str)
{
	if (*var)
	{
		while (*var)
		{
			result[i] = *var;
			i++;
			var++;
		}
		attach_suffix(str, result, i);
	}
	free(str);
	return (result);
}

char	*replace_extend_var(char *str, char *var)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(var) + 100000));
	while (str[i] && str[i] != '$')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = var[j];
	i++;
	j++;
	while (str[i] >= 'A' && str[i] <= 'Z')
	{
		result[i] = var[j];
		i++;
		j++;
	}
	result = extend_var(&var[j], result, i, str);
	return (result);
}
