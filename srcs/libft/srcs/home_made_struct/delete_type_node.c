/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_type_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:30:51 by llescure          #+#    #+#             */
/*   Updated: 2022/03/09 17:28:11 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	delete_type_node(t_type	**type)
{
	t_type	*temp;

	temp = (*type)->next;
	(*type)->next = temp->next;
	if ((*type)->next != NULL)
		(*type)->next->previous = temp->previous;
	free(temp);
}
