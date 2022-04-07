/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:07:52 by llescure          #+#    #+#             */
/*   Updated: 2022/04/07 08:07:55 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_special_condition_cara(t_type type)
{
	if (type == QUOTE || type == WORD || type == D_QUOTE
		|| type == EXPAND)
		return (1);
	return (0);
}

int	look_for_word_in_type(t_token *token, t_type type)
{
	while (token != NULL)
	{
		if (token->type == type)
			return (1);
		token = token->next;
	}
	return (0);
}

void	join_quote_word_expand(t_token **token)
{
	char	*str_temp;

	while ((*token)->next != NULL
		&& check_special_condition_cara((*token)->next->type) == 1)
	{
		str_temp = (*token)->content;
		(*token)->content = ft_strjoin(str_temp,
				(*token)->next->content);
		free(str_temp);
		delete_token_node(token);
	}
}
