#include "../../include/minishell.h"

void	define_pipe_input_output(t_command *command, t_token *token)
{
	command->pipe_input = 0;
	command->pipe_output = 0;
	look_for_pipe_before_command(command, token);
	look_for_pipe_after_command(command, token);
}

void	look_for_pipe_before_command(t_command *command, t_token *token)
{
/*	int	compt;

	compt = 0;
	while (token != NULL && compt != token->id)
	{
		token = token->next;
		compt++;
	}*/
	while (token->previous != NULL)
	{
		if (token->type == PIPE)
		{
			command->pipe_output = 1;
			break;
		}
		token = token->previous;
	}
}

void	look_for_pipe_after_command(t_command *command, t_token *token)
{
/*	int compt;

	compt = 0;
	while (token != NULL && compt != token->id)
	{
		token = token->next;
		compt++;
	}*/
	while (token->next != NULL)
	{
		if (token->type == PIPE)
		{
			command->pipe_input = 1;
			break;
		}
		token = token->next;
	}
}
