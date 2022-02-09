/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:48:18 by llescure          #+#    #+#             */
/*   Updated: 2022/02/08 15:50:06 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_double_free_list(t_double_list **list)
{
	t_double_list	*temp;

	if (*list == NULL || list == NULL)
		return ;
	while ((*list)->next != NULL)
	{
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
	free(*list);
	*list = NULL;
}
