/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multiple_cara.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:19:14 by llescure          #+#    #+#             */
/*   Updated: 2022/02/14 16:30:57 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

unsigned long	ft_count_words_multiple(char const *s, char sep1, char sep2)
{
	unsigned long	i;
	unsigned long	compt;

	i = 0;
	compt = 0;
	while (s[i] != '\0')
	{
		if (s[i] != sep1 && (s[i + 1] == sep1 || (s[i + 1] == '\0')))
			compt++;
		if (s[i] != sep2 && (s[i + 1] == sep2 || (s[i + 1] == '\0')))
			compt++;
		if (s[i + 1] == '\0')
			break ;
		i++;
	}
	return (compt);
}

unsigned long	ft_m_cara(char const *s, char sep1, int pos, char sep2)
{
	unsigned long	i;
	unsigned long	compt;

	i = pos;
	compt = 0;
	while (s[i] == sep1 || s[i] == sep2)
		i++;
	while (s[i] != sep1 && s[i] != sep2 && s[i] != '\0')
	{
		compt++;
		i++;
	}
	return (compt);
}

char	**ft_split_multiple_cara(char const *s, char c1, char c2)
{
	char						**tab;
	unsigned long				i;
	unsigned long				pos;

	i = 0;
	pos = 0;
	tab = malloc(sizeof(char *) * (ft_count_words_multiple(s, c1, c2) + 1));
	while (i < ft_count_words_multiple(s, c1, c2))
	{
		tab[i] = (char *)malloc(sizeof(char) * (ft_m_cara(s, c1, pos, c2) + 1));
		if (!tab[i])
		{
			ft_free(tab, i);
			return (NULL);
		}
		while (s[pos] == c1 || s[pos] == c2)
			pos++;
		ft_memcpy(tab[i], s + pos, ft_m_cara(s, c1, pos, c2));
		tab[i][ft_m_cara(s, c1, pos, c2)] = '\0';
		pos += ft_m_cara(s, c1, pos, c2);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
