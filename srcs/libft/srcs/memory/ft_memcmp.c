/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 23:16:59 by llescure          #+#    #+#             */
/*   Updated: 2021/12/14 16:16:54 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int			i;
	const char				*temps1;
	const char				*temps2;

	i = 0;
	temps1 = s1;
	temps2 = s2;
	while (i < n)
	{
		if (temps1[i] != temps2[i])
			return ((unsigned char)temps1[i] - (unsigned char)temps2[i]);
		i++;
	}
	return (0);
}
