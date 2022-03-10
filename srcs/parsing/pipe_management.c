#include "../../include/minishell.h"

void	define_pipe_input_output(t_command *command, t_type *type, int id)
{
	command->pipe_input = 0;
	command->pipe_output = 0;
	look_for_pipe_before_command(command, type, id);
	look_for_pipe_after_command(command, type, id);
}

void	look_for_pipe_before_command(t_command *command, t_type *type, int id)
{
	int	compt;

	compt = 0;
	while (type != NULL && compt != id)
	{
		type = type->next;
		compt++;
	}
	while (type->previous != NULL)
	{
		if (type->content == PIPE)
		{
			command->pipe_output = 1;
			break;
		}
		type = type->previous;
	}
}

void	look_for_pipe_after_command(t_command *command, t_type *type, int id)
{
	int compt;

	compt = 0;
	while (type != NULL && compt != id)
	{
		type = type->next;
		compt++;
	}
	while (type->next != NULL)
	{
		if (type->content == PIPE)
		{
			command->pipe_input = 1;
			break;
		}
		type = type->next;
	}
}
