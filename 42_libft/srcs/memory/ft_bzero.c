/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 23:11:10 by llescure          #+#    #+#             */
/*   Updated: 2021/05/06 15:22:44 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_bzero(void *s, size_t n)
{
	char				*temp;
	unsigned int		i;

	temp = s;
	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
}
