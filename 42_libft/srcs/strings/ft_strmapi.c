/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 23:35:11 by llescure          #+#    #+#             */
/*   Updated: 2021/12/14 16:28:20 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	unsigned int				i;
	char						*final;

	final = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!final)
		return (NULL);
	ft_strlcpy(final, s, ft_strlen(s));
	i = 0;
	while (s[i] != '\0')
	{
		final[i] = f(i, s[i]);
		i++;
	}
	final[i] = '\0';
	return (final);
}
