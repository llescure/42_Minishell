/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:32:15 by llescure          #+#    #+#             */
/*   Updated: 2022/03/07 18:43:23 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_free_type(t_type **list)
{
	t_type	*temp;

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
