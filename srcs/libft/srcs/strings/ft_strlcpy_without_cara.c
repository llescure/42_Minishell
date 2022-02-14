/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy_without_cara.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:42:21 by llescure          #+#    #+#             */
/*   Updated: 2022/02/10 17:50:27 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int			ft_strlcpy_without_cara(char *dst, char *src, char cara)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (src[j] != '\0')
	{
		while (src[j] == cara)
			j++;
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ft_strlen((char *)dst));
}
