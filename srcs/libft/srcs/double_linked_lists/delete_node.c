/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:30:49 by llescure          #+#    #+#             */
/*   Updated: 2022/02/18 09:40:58 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	delete_node(t_double_list	**list, int free_content)
{
	t_double_list	*temp;

	temp = (*list)->next;
	(*list)->next = temp->next;
	if ((*list)->next != NULL)
		(*list)->next->previous = temp->previous;
	if (free_content == 1)
		free(temp->content);
	free(temp);
}
