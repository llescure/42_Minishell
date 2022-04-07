/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_management2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:00:42 by llescure          #+#    #+#             */
/*   Updated: 2022/04/07 08:00:45 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 ** This function splits the string into a tab if it encounters a $
 ** or simple quote
 */

char	**split_expand(char *str, char cara)
{
	int		j;
	int		i;
	char	**tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (ft_count_words_multiple(str, cara, '\'')
				+ 2));
	if (tab == NULL)
	{
		g_signal = -1;
		return (NULL);
	}
	while (str[i] != '\0')
	{
		tab[j] = find_lexeme(str, i, &i, 1);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
