/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstfirst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:06:22 by llescure          #+#    #+#             */
/*   Updated: 2021/12/14 15:59:43 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_double_list	*ft_double_lstfirst(t_double_list *lst)
{
	t_double_list	*new;

	if (lst == NULL)
		return (NULL);
	new = lst;
	while (new->previous != NULL)
		new = new->previous;
	return (new);
}
