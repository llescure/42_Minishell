/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scanner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:08:04 by llescure          #+#    #+#             */
/*   Updated: 2022/04/20 14:04:04 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_cut_str(char *user_input, int beginning, int end)
{
	char	*new_str;
	int		i;
	int		j;

	i = beginning;
	j = 0;
	if (end - beginning <= 0)
		return (NULL);
	new_str = malloc(sizeof(char) * end - beginning + 1);
	if (new_str == NULL)
	{
		g_signal = -1;
		return (new_str);
	}
	while (j < end - beginning && user_input[i] != '\0')
	{
		new_str[j] = user_input[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

/*
 ** When a single quote or double quote is encountered this function looks for
 ** the next one. If none were found, the quote is skipped
 */

int	look_for_quote(char *str, int pos, char type_quote, int initial_pos)
{
	int	i;

	if (str[initial_pos] != type_quote)
		return (pos);
	i = pos;
	i++;
	while (str[i] != type_quote && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (pos + 1);
	return (i + 1);
}

int	delimit_separator(char *str, int pos, char separator, int initial_pos)
{
	int	i;
	int	first_true;

	first_true = 0;
	i = pos;
	if (pos > 0 && (pos - 1 == 0 || ft_iscara(str[pos - 1], separator) == 0))
		first_true = 1;
	i++;
	while (ft_iscara(str[i], separator) == 1 && str[i] != '\0')
		i++;
	if (first_true == 1 && ft_isspace(str[pos - 1]) == 0 && i - 1 > initial_pos)
		return (pos);
	return (i);
}

int	delimit_expand(char *str, int pos, int initial_pos)
{
	int	i;

	if (str[initial_pos] != '$')
		return (pos);
	i = pos;
	i++;
	while (ft_isspace(str[i]) == 0 && str[i] != '\0' && (ft_isalnum(str[i]) == 1
			|| str[i] == '?'))
	{
		if (str[i] == '?')
			return (i + 1);
		i++;
	}
	return (i);
}

int	delimit_redirections(char *str, int pos, int initial_pos)
{
	int	i;

	if (ft_isredirections(str[initial_pos]) == 0)
		return (pos);
	i = pos;
	while (ft_isredirections(str[i]) == 1)
	i++;
	while (ft_isspace(str[i]) == 1)
		i++;
	while (ft_isspace(str[i]) == 0 && str[i] != '\0'
		&& (ft_isascii(str[i]) == 1 || ft_isredirections(str[i]) == 1))
		i++;
	return (i);
}
