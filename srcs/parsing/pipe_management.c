/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:01:25 by llescure          #+#    #+#             */
/*   Updated: 2022/04/15 10:19:58 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	define_pipe_input_output(t_command *command, t_token *token)
{
	command->pipe_in = 0;
	command->pipe_out = 0;
	if (look_for_type_before_command(token, PIPE) == 1)
		command->pipe_out = 1;
	if (look_for_type_after_command(token, PIPE) == 1)
		command->pipe_in = 1;
	if (command->pipe_in == 0 && command->pipe_out == 0
		&& (token->previous != NULL))
	{
		token = token->previous;
		if (look_for_type_before_command(token, COMMAND) == 1)
			command->command_type = VOID;
	}
}

int	look_for_type_before_command(t_token *token, t_type type)
{
	while (token != NULL)
	{
		if (token->type == type)
			return (1);
		token = token->previous;
	}
	return (0);
}

int	look_for_type_after_command(t_token *token, t_type type)
{
	while (token != NULL)
	{
		if (token->type == type)
			return (1);
		token = token->next;
	}
	return (0);
}
