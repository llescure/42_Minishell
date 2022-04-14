/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:07:52 by llescure          #+#    #+#             */
/*   Updated: 2022/04/14 09:05:15 by llescure         ###   ########.fr       */
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
		else if (token->type == EXPAND ||token->type == D_QUOTE
				|| token->type == QUOTE || token->type == ERROR)
			token->type = WORD;
	}
}

void	delete_word_in_command(t_token *token, t_command *command)
{
	while (command != NULL)
	{
		while (token != NULL && token->id != command->id)
			token = token->next;
		if (token == NULL)
			return ;
		if (token->id == command->id && token->type == WORD)
			command->command_type = VOID;
		command = command->next;
	}
}

t_type	previous_type(t_token *token)
{
	while (token != NULL && token->type == WHITE_SPACE)
		token = token->previous;
	if (token != NULL)
		return (token->type);
	else
		return (ERROR);
}

void	delete_empty_word(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == WORD && double_ft_strncmp(token->content, "") == 1)
			token->type = WHITE_SPACE;
		token = token->next;
	}
}

void	delete_multiple_space(t_token *token)
{
	while (token->next != NULL)
	{
		while (token->type == WHITE_SPACE && token->next->type == WHITE_SPACE
				&& token->next->next != NULL)
			delete_token_node(&token);
		token = token->next;
	}
}
