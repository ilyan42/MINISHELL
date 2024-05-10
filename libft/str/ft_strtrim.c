/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanson <elanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:57:10 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/16 13:12:27 by elanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	len_dest(char const *set, char const *s1)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && is_set(set, s1[start]))
		start++;
	while (end > start && is_set(set, s1[end - 1]))
		end--;
	return (end - start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	i;
	int		len;

	if (!s1 || !set)
		return (NULL);
	len = len_dest(set, s1);
	if (len <= 0)
		return (ft_strdup(""));
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (is_set(set, s1[i]))
		i++;
	ft_strlcpy(dest, &s1[i], len + 1);
	return (dest);
}
