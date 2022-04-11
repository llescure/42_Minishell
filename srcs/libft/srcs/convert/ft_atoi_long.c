/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:38:08 by llescure          #+#    #+#             */
/*   Updated: 2022/04/11 11:39:06 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

long long	ft_atoi_long(const char *str)
{
	int						i;
	long long				rslt;
	long					sign;

	i = 0;
	rslt = 0;
	sign = ft_check_sign(str);
	if (sign == 0)
		return (0);
	while (str[i] == '-' || str[i] == '+' || ft_is_white_space(str[i]) == 1)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rslt = rslt * 10 + str[i] - '0';
		i++;
	}
	return (sign * rslt);
}
