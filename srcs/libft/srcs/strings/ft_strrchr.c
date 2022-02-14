/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 23:36:37 by llescure          #+#    #+#             */
/*   Updated: 2022/02/10 11:25:36 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				i;

	i = (int)ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == c)
			return ((char *)&str[i + 1]);
		i--;
	}
	return (NULL);
}
