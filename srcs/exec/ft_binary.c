#include "../../include/minishell.h"

void	execute_binary(t_shell *shell, t_token *token)
{
	char	*temp;
	char	**command;

	if (shell->path != NULL)
	{
		free(shell->path);
		shell->path = NULL;
	}
	set_path(shell);
	command = create_binary(token);
	if (command == NULL)
		exit(error_system(shell, MALLOC));
	if (shell->path != NULL)
	{
		temp = command[0];
		command[0] = find_correct_path(shell->path, command[0]);
		free(temp);
	}
	if (execve(command[0], command, shell->env->env) < 0)
	{
		error_message(COMMAND_ERROR, 1);
		free_tab(command);
		exit(g_signal);
	}
	free_tab(command);
}

char	**create_binary(t_token *token)
{
	char	**command;
	int		i;

	command = malloc(sizeof(char *) * (command_lenght(token) + 1));
	if (command == NULL)
		return (NULL);
	i = 0;
	while (token != NULL && (token->type == WHITE_SPACE
			|| token->type == COMMAND_OPTION || token->type == COMMAND
			|| token->type == WORD))
	{
		if (token->type == WHITE_SPACE)
			token = token->next;
		if (token == NULL
			|| (token->type != WORD && token->type != COMMAND_OPTION
				&& token->type != COMMAND))
			break ;
		command[i] = ft_strdup(token->content);
		token = token->next;
		i++;
	}
	command[i] = NULL;
	return (command);
}

int	command_lenght(t_token *token)
{
	int	size;

	size = 1;
	while (token != NULL && (token->type == WHITE_SPACE
			|| token->type == COMMAND_OPTION || token->type == COMMAND
			|| token->type == WORD))
	{
		if (token->type == WHITE_SPACE)
			token = token->next;
		if (token == NULL)
			break ;
		size++;
		token = token->next;
	}
	return (size);
}
