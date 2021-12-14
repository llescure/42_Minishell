/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstdelone.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:16:45 by llescure          #+#    #+#             */
/*   Updated: 2021/05/12 11:18:39 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_double_lstdelone(t_double_list **lst, int pos)
{
	t_double_list	*temp;

	if (*lst == NULL || pos < 0)
		return ;
	temp = *lst;
	while (temp->previous != NULL)
		temp = temp->previous;
	if (pos == 0)
		case_first_node(&temp);
	else if (pos == ft_double_lstsize(temp))
		case_last_node(&temp);
}

void	case_first_node(t_double_list **lst)
{
	t_double_list	*temp;

	temp = *lst;
	*lst = temp->next;
	temp->next->previous = temp->next;
	free(temp);
}

void	case_last_node(t_double_list **lst)
{
	t_double_list	*temp;

	while ((*lst)->next != NULL)
		*lst = (*lst)->next;
	temp = *lst;
	*lst = temp->previous;
	temp->previous->next = temp->previous;
	free(temp);
}
