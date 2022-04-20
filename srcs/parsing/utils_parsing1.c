/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:07:52 by llescure          #+#    #+#             */
/*   Updated: 2022/04/20 14:23:12 by llescure         ###   ########.fr       */
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

void	transform_expand_quote_command(t_token *token)
{
	char	*str;

	while (token != NULL)
	{
		if (token->type == EXPAND || token->type == D_QUOTE
			|| token->type == QUOTE)
		{
			str = token->content;
			if (ft_isascii(str[0]) == 1)
				token->type = COMMAND;
		}
			token = token->next;
	}
}

void	find_word_in_token(t_token *token)
{
	while (token->next != NULL && token->type != COMMAND)
		token = token->next;
	if (token->next != NULL)
		token = token->next;
	if (token == NULL)
		return ;
	while (token->next != NULL)
	{
		while (token->next != NULL && token->type != PIPE)
		{
			if (token->type == COMMAND || token->type == EXPAND
				|| token->type == D_QUOTE || token->type == QUOTE
				|| token->type == ERROR)
				token->type = WORD;
			token = token->next;
		}
		while (token->next != NULL && token->type != COMMAND)
			token = token->next;
		if (token->next != NULL)
			token = token->next;
	}
	if (token->type != PIPE)
	{
		if (token->type == COMMAND
			&& previous_type(token->previous) != PIPE
			&& previous_type(token->previous) != ERROR)
			token->type = WORD;
		else if (token->type == EXPAND || token->type == D_QUOTE
			|| token->type == QUOTE || token->type == ERROR)
			token->type = WORD;
	}
}
