#include "../../include/minishell.h"

int		initialization_command(t_type *type, t_double_list *token,
		t_shell *shell)
{
	while (type != NULL && token != NULL)
	{
		if (type->content == COMMAND)
		{
			if (shell->command == NULL)
			{
				shell->command = create_command_struct(token->content, type,
						token, type->id);
				if (g_signal < 0)
					return(g_signal);
			}
			else
			{
				if (append_command_struct(&shell->command, token->content,
							shell, type->id) < 0)
					return(g_signal);
			}
		}
		type = type->next;
		token = token->next;
	}
	return (0);
}

t_command	*create_command_struct(char *str, t_type *type,
		t_double_list *token, int id)
{
	t_command	*new_command;

	new_command = malloc(sizeof(*new_command));
	if (new_command == NULL)
	{
		error_message(MALLOC, 1);
		return(NULL);
	}
	if (ft_strncmp(str, "exit", ft_strlen("exit")) == 0
		&& ft_strncmp(str, "exit", ft_strlen(str)) == 0)
	new_command->command_type = EXIT;
	else if (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0
		&& ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
	new_command->command_type = PWD;
	else if (ft_strncmp(str, "echo", ft_strlen("echo")) == 0
		&& ft_strncmp(str, "echo", ft_strlen(str)) == 0)
	new_command->command_type = ECHO_CMD;
	else if (ft_strncmp(str, "cd", ft_strlen("cd")) == 0
		&& ft_strncmp(str, "cd", ft_strlen(str)) == 0)
	new_command->command_type = CD;
	else if (ft_strncmp(str, "export", ft_strlen("export")) == 0
		&& ft_strncmp(str, "export", ft_strlen(str)) == 0)
	new_command->command_type = EXPORT;
	else if (ft_strncmp(str, "unset", ft_strlen("unset")) == 0
		&& ft_strncmp(str, "unset", ft_strlen(str)) == 0)
	new_command->command_type = UNSET;
	else if (ft_strncmp(str, "env", ft_strlen("env")) == 0
		&& ft_strncmp(str, "env", ft_strlen(str)) == 0)
	new_command->command_type = ENV;
	else
		new_command->command_type = BINARY;
	new_command->next = NULL;
	new_command->id = id;
	attach_redirections_to_command(new_command, type, token);
	define_pipe_input_output(new_command, type, id);
	return(new_command);
}

int		append_command_struct(t_command **command, char *str, t_shell *shell,
		int id)
{
	t_command	*temp;

	temp = *command;
	while((temp)->next != NULL)
		temp = temp->next;
	temp->next = create_command_struct(str, shell->type, shell->token, id);
	if (temp->next == NULL)
		return(error_malloc(shell));
	return (0);
}

void	free_redirection(t_redirection **redirection)
{
	t_redirection	*temp;

	if (*redirection == NULL || redirection == NULL)
		return ;
	while ((*redirection)->next != NULL)
	{
		temp = (*redirection)->next;
		free(*redirection);
		*redirection = temp;
	}
	free(*redirection);
	*redirection = NULL;
}

void	free_command(t_command	**command)
{
	t_command	*temp;

	if (*command == NULL || command == NULL)
		return ;
	while ((*command)->next != NULL)
	{
		temp = (*command)->next;
		free_redirection(&(*command)->redirection);
		free(*command);
		*command = temp;
	}
	free_redirection(&(*command)->redirection);
	free(*command);
	*command = NULL;
}
