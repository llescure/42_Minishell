/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:21:24 by llescure          #+#    #+#             */
/*   Updated: 2022/04/21 17:37:06 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		while (token->type == WHITE_SPACE && token->next->next != NULL
			&& (token->next->type == WHITE_SPACE
				|| token->next->type == EMPTY))
			delete_token_node(&token);
		token = token->next;
	}
}
