/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:47:00 by llescure          #+#    #+#             */
/*   Updated: 2021/12/14 16:10:08 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_element;

	new_list = NULL;
	if ((lst == NULL) || !(*f) || !(*del))
		return (NULL);
	while (lst != NULL)
	{
		new_element = ft_lstnew((*f)(lst->content));
		if (new_element == NULL)
			ft_lstdelone(new_element, *del);
		if (new_list == NULL)
			new_list = new_element;
		else
			ft_lstadd_back(&new_list, new_element);
		lst = lst->next;
	}
	return (new_list);
}
