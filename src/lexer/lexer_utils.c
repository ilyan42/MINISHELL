/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:05:07 by ilbendib          #+#    #+#             */
/*   Updated: 2024/03/26 15:32:11 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_type_token	*ft_lstlast_node(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
	{
		token = token->next;
	}
	return (token);
}

int ft_add_node(t_token *token, t_token *node)
{
	t_token	*last;

	if (!node)
		return (0);
	last = ft_lstlast_node(token);
	last->next = node;
	node->prev = last;
	return (1);
}

int	ft_create_node(t_token *token, char *value, int linked)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = value;
	new->index = token->index + 1;
	new->linked = false;
	new->next = NULL;
	new->prev = token;
	token->next = new;
	return (1);
}

int ft_strndup(char **dest, char *src, int n)
{
	int	i;

	i = 0;
	*dest = (char *)malloc(sizeof(char) * (n + 1));
	if (!*dest)
		return (0);
	while (src[i] && i < n)
	{
		(*dest)[i] = src[i];
		i++;
	}
	(*dest)[i] = '\0';
	return (1);
}

void	ft_lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*head;
	t_token	*next;

	if (!*lst)
		return ;
	head = *lst;
	while (head)
	{
		next = head -> next;
		ft_lstdelone(head, del);
		head = next;
	}
	*lst = NULL;
}

void	ft_lstdelone(t_token *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	(*del)(lst -> value);
	free(lst);
}