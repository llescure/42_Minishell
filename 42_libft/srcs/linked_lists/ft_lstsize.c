/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 19:47:38 by llescure          #+#    #+#             */
/*   Updated: 2021/05/12 10:37:51 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		compt;
	t_list	*temp;

	compt = 0;
	if (lst == NULL)
		return (0);
	temp = lst;
	while (temp != NULL)
	{
		compt++;
		temp = temp->next;
	}
	return (compt);
}
