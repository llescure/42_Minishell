/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:47:55 by llescure          #+#    #+#             */
/*   Updated: 2022/05/02 14:39:53 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	execute_binary(t_shell *shell, t_token *token, int exit_or_return)
{
	char	*temp;
	char	**command;

	if (double_ft_strncmp(token->content, ""))
		exit(g_signal);
	command = create_binary(token);
	if (command == NULL)
		exit(error_system(shell, MALLOC));
	if (shell->path != NULL && find_cara_in_word(command[0], '/') == -1)
	{
		temp = command[0];
		command[0] = find_correct_path(shell->path, command[0]);
		free(temp);
	}
	g_signal = 0;
	if (execve(command[0], command, shell->env->env) < 0)
	{
		case_execve_fail(shell, exit_or_return, command);
		return ;
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

void	case_execve_fail(t_shell *shell, int exit_or_return, char **command)
{
	free_tab(command);
	error_message(COMMAND_ERROR, STDERR_FILENO);
	if (shell->fd_pipe_in != STDIN_FILENO)
		close(shell->fd_pipe_in);
	if (shell->fd_in > 0 || shell->fd_out > 0)
		reset_fd(shell);
	if (exit_or_return == 1)
	{
		free_all(shell);
		exit(g_signal);
	}
}
