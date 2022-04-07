/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:01:35 by llescure          #+#    #+#             */
/*   Updated: 2022/04/07 08:01:38 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	single_quote_expansion(t_shell *shell, t_token **token)
{
	quote_expansion(shell, token, QUOTE);
}

void	double_quote_expansion(t_shell *shell, t_token **token)
{
	quote_expansion(shell, token, D_QUOTE);
}

/*
 ** This function spots all the occurence of quotes in the user_input string,
 ** creates new strings without the quote and makes sure that everything is
 ** freed. It also makes sure that there is not other expansion character.
 */

void	quote_expansion(t_shell *shell, t_token **token, t_type type_expansion)
{
	while ((*token)->next != NULL)
	{
		if ((*token)->type == type_expansion)
			quote_cases(shell, (char **)&(*token)->content, type_expansion);
		*token = (*token)->next;
	}
	if ((*token)->type == type_expansion)
		quote_cases(shell, (char **)&(*token)->content, type_expansion);
	while ((*token)->previous != NULL)
		*token = (*token)->previous;
}

void	quote_cases(t_shell *shell, char **str, t_type type_expansion)
{
	char	*temp;

	if (type_expansion == D_QUOTE && find_cara_in_word(*str, '$') >= 0)
		expansion_cases(shell, str);
	temp = *str;
	if (type_expansion == D_QUOTE)
		*str = remove_cara(*str, '"');
	else
		*str = remove_cara(*str, '\'');
	free(temp);
}

char	*remove_cara(char *str, char type_cara_to_delete)
{
	char	*cpy;
	int		nbr_occurence;

	nbr_occurence = number_occurence_cara_in_str(str, type_cara_to_delete);
	cpy = malloc(sizeof(char) * (ft_strlen(str) - nbr_occurence + 1));
	if (cpy == NULL)
		return (NULL);
	ft_strlcpy_without_cara(cpy, str, type_cara_to_delete);
	return (cpy);
}
