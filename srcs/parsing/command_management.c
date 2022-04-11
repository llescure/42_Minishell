/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 07:59:34 by llescure          #+#    #+#             */
/*   Updated: 2022/04/11 07:40:13 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	initialization_command(t_token *token, t_shell *shell)
{
	while (token != NULL)
	{
		if (token->type == COMMAND)
		{
			if (shell->command == NULL)
			{
				shell->command = create_command_struct(token->content, token);
				if (g_signal < 0)
					return (g_signal);
			}
			else
			{
				if (append_command_struct(&shell->command, token, shell) < 0)
					return (g_signal);
			}
		}
		token = token->next;
	}
	return (0);
}

t_command	*create_command_struct(char *str, t_token *token)
{
	t_command	*new_command;

	new_command = malloc(sizeof(*new_command));
	if (new_command == NULL)
	{
		error_message(MALLOC, 1);
		return (NULL);
	}
	find_type_command(str, &new_command);
	new_command->next = NULL;
	new_command->id = token->id;
	attach_redirections_to_command(new_command, token);
	define_pipe_input_output(new_command, token);
	return (new_command);
}

int	append_command_struct(t_command **command, t_token *token,
		t_shell *shell)
{
	t_command	*temp;

	temp = *command;
	while ((temp)->next != NULL)
		temp = temp->next;
	temp->next = create_command_struct(token->content, token);
	if (temp->next == NULL)
		return (error_system(shell, MALLOC));
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
		free((*redirection)->file);
		free(*redirection);
		*redirection = temp;
	}
	free((*redirection)->file);
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
