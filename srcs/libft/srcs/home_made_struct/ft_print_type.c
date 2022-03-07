/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:33:50 by llescure          #+#    #+#             */
/*   Updated: 2022/03/07 16:34:30 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_print_type(t_type *lst)
{
	int	compt;

	compt = 0;
	if (lst == NULL)
		return ;
	while (lst->next != NULL)
	{
		printf("compt = %d content = %d\n", compt, (int)(*lst).content);
		compt++;
		lst = lst->next;
	}
	printf("compt = %d content = %d\n", compt, (int)(*lst).content);
}
