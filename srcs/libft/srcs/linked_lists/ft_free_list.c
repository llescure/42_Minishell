/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:54:07 by llescure          #+#    #+#             */
/*   Updated: 2022/04/05 20:20:21 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_free_list(t_list **list, int free_content)
{
	t_list	*temp;

	if (*list == NULL || list == NULL)
		return ;
	while ((*list)->next != NULL)
	{
		temp = (*list)->next;
		if (free_content == 1)
			free((*list)->content);
		free(*list);
		*list = temp;
	}
	if (free_content == 1)
		free((*list)->content);
	free(*list);
	*list = NULL;
}
