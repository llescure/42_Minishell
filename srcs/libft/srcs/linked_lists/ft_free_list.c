/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:54:07 by llescure          #+#    #+#             */
/*   Updated: 2022/01/25 17:24:40 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_free_list(t_list **list)
{
	t_list	*temp;
	t_list	*temp2;

	temp2 = *list;
	if (*list == NULL || list == NULL)
		return ;
	while (temp2 != NULL)
	{
		temp = temp2->next;
		free(temp2->content);
		temp2 = temp;
	}
	*list = temp2;
}
