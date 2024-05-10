/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tknlist_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbendib <ilbendib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:47:59 by ilbendib          #+#    #+#             */
/*   Updated: 2024/04/30 17:11:00 by ilbendib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pop_token_in_place(t_tknlist *list_tkn, t_token *to_pop)
{
	if (to_pop == NULL)
		return ;
	if (to_pop != list_tkn->head)
		(to_pop->previous)->next = to_pop->next;
	else
		list_tkn->head = to_pop->next;
	if (to_pop != list_tkn->tail)
		(to_pop->next)->previous = to_pop->previous;
	else
		list_tkn->tail = to_pop->previous;
	if (to_pop->content)
		del_one_garbage(to_pop->content, TKN_LIST);
	del_one_garbage(to_pop, TKN_LIST);
}

void	add_tknlst_in_tknlst_after_target(t_tknlist *lst1 \
			, t_token *tkn_flag, t_tknlist *lst2)
{
	if (!lst1 || !lst1->head || !tkn_flag || !lst2 || !lst2->head)
		return ;
	if (tkn_flag == lst1->tail)
		lst1->tail = lst2->tail;
	else
	{
		(lst2->tail)->next = tkn_flag->next;
		(tkn_flag->next)->previous = lst2->tail;
	}
	(lst2->head)->previous = tkn_flag;
	tkn_flag->next = (lst2->head);
}

void	swap_tokens(t_tknlist	*lst, t_token *tkn1, t_token *tkn2)
{
	t_token	*tmp_previous;

	if (tkn1 == NULL || tkn2 == NULL \
		|| lst == NULL || lst->head == NULL || lst->tail == NULL)
		return ;
	tmp_previous = tkn1->previous;
	if (tkn1 == lst->head)
		lst->head = tkn2;
	else
		(tkn1->previous)->next = tkn2;
	if (tkn2 == lst->tail)
		lst->tail = tkn1;
	else
		(tkn2->next)->previous = tkn1;
	tkn1->previous = tkn2;
	tkn1->next = tkn2->next;
	tkn2->previous = tmp_previous;
	tkn2->next = tkn1;
}

size_t	tknlst_size(t_tknlist *tknlst)
{
	t_token	*curr;
	size_t	i;

	curr = tknlst->head;
	i = 0;
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}
