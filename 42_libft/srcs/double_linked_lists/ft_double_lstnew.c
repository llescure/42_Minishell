/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstnew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:05:29 by llescure          #+#    #+#             */
/*   Updated: 2021/12/14 16:00:58 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_double_list	*ft_double_lstnew(void *content)
{
	t_double_list	*new_list;

	new_list = malloc(sizeof(*new_list));
	if (!new_list)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	new_list->previous = NULL;
	return (new_list);
}
