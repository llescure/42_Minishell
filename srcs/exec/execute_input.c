/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:50:17 by llescure          #+#    #+#             */
/*   Updated: 2022/04/25 20:32:01 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_input(t_shell *shell, t_token *token, t_command *command)
{
	shell->fd_in = 0;
	shell->fd_out = 0;
	while (token != NULL)
	{
		if (token->type == COMMAND)
		{
			if (command->pipe_in == 1 || command->pipe_out == 1)
				return (handle_pipe(shell, command, token));
			else
				launch_command(shell, token, command);
			if (token == NULL)
				return (0);
			command = command->next;
		}
		token = token->next;
	}
	return (0);
}

void	launch_command(t_shell *shell, t_token *token, t_command *command)
{
	if (command->redirection != NULL)
		return (handle_redirection(command, shell, token));
	handle_command(shell, token, command);
}

void	handle_command(t_shell *shell, t_token *token, t_command *command)
{
	if (command->command_type == PWD)
		ft_pwd(shell);
	else if (command->command_type == ENV)
		print_env(shell->env->env);
	else if (command->command_type == EXIT)
		ft_exit(shell, token, command);
	else if (command->command_type == ECHO_CMD)
		ft_echo(token);
	else if (command->command_type == CD)
		ft_cd(shell, token, command);
	else if (command->command_type == EXPORT)
		ft_export(shell, token);
	else if (command->command_type == UNSET)
		ft_unset(shell, token);
	else if (command->command_type == BINARY
		|| command->command_type == EXECUTABLE)
	{
		if (shell->path != NULL)
		{
			free_tab(shell->path);
			shell->path = NULL;
		}
		set_path(shell);
		execute_child_process(shell, token, command);
	}
}

int	execute_child_process(t_shell *shell, t_token *token,
		t_command *command)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (error_system(shell, PIPE_FORK));
	else if (pid == 0)
	{
		if (command->command_type == BINARY)
			execute_binary(shell, token, 1);
		else if (command->command_type == EXECUTABLE)
			execute_executable(shell, token);
	}
	else
	{
		signal(SIGINT, handle_exec_signals);
		signal(SIGQUIT, handle_exec_signals);
		waitpid(pid, &g_signal, 0);
		g_signal = WEXITSTATUS(g_signal);
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, handle_signals);
	}
	return (0);
}
