/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 23:26:56 by llescure          #+#    #+#             */
/*   Updated: 2022/02/10 11:31:53 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned long	i;

	i = 0;
	if (c == '\0' && str[0] == '\0')
		return ((char *)str);
	while (i <= ft_strlen(str))
	{
		if (c == str[i])
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}
