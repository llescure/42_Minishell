/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:21:09 by llescure          #+#    #+#             */
/*   Updated: 2022/02/07 17:21:18 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_print_list(t_list *lst)
{
	int compt;

	compt = 0;
	if (lst == NULL)
		return ;
	while (lst->next != NULL)
	{
		printf("compt = %d content = %s\n", compt, (char *)(*lst).content);
		compt++;
		lst = lst->next;
	}
	printf("compt = %d content = %s\n", compt, (char *)(*lst).content);
}