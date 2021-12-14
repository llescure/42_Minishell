/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstadd_front.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:05:00 by llescure          #+#    #+#             */
/*   Updated: 2021/05/12 10:57:56 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_double_lstadd_front(t_double_list **alst, t_double_list *new)
{
	new->previous = NULL;
	new->next = *alst;
	if (*alst != NULL)
		(*alst)->previous = new;
	*alst = new;
}
