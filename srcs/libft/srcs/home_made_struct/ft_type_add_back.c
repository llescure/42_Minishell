/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:30:25 by llescure          #+#    #+#             */
/*   Updated: 2022/03/07 16:31:41 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_type_add_back(t_type **alst, t_type *new)
{
	t_type *temp;

	if (alst == NULL)
		return ;
	new->next = NULL;
	temp = *alst;
	if (temp == NULL)
	{
		new->previous = NULL;
		temp = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	new->previous = temp;
	temp->next = new;
}
