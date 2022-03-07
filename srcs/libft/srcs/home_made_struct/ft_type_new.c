/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:28:21 by llescure          #+#    #+#             */
/*   Updated: 2022/03/07 18:20:07 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_type	*ft_type_new(t_category content)
{
	t_type *new_list;

	if (!(new_list = malloc(sizeof(*new_list))))
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	new_list->previous = NULL;
	return (new_list);
}
