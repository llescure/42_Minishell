/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_print_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:10:20 by llescure          #+#    #+#             */
/*   Updated: 2022/03/03 11:57:10 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_double_print_list_char(t_double_list *lst)
{
	int	compt;

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

void	ft_double_print_list_int(t_double_list *lst)
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
