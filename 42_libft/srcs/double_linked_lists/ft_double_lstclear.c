/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstclear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:35:01 by llescure          #+#    #+#             */
/*   Updated: 2021/12/14 16:41:11 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_double_lstclear(t_double_list **lst, t_double_list *del)
{
	t_double_list	*temp;

	if (*lst == NULL || del == NULL)
		return ;
	while ((*lst)->previous != NULL)
		*lst = (*lst)->previous;
	while ((*lst)->next != NULL)
	{
		if (*lst == del)
		{
			while (del->next != NULL)
			{
				temp = (*lst)->next;
				free(del);
				free(*lst);
			}
		}
		*lst = (*lst)->next;
	}
}
