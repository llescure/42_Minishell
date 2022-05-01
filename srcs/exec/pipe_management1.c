/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:47:46 by llescure          #+#    #+#             */
/*   Updated: 2022/05/01 18:57:59 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_pipe(t_shell *shell, t_command *command, t_token *token)
{
	pid_t	pid;

	shell->fd_pipe_in = STDIN_FILENO;
	while (command != NULL)
	{
		if (pipe(shell->fd) < 0)
			return (error_system(shell, PIPE_FORK));
		pid = fork();
		if (pid < 0)
			return (error_system(shell, PIPE_FORK));
		else if (pid == 0)
			child_process(shell, token, command);
		else
		{
			parent_process(pid, shell);
			command = command->next;
			while (command != NULL && token != NULL && token->id < command->id)
				token = token->next;
		}
	}
	close(shell->fd[1]);
	close(shell->fd[0]);
	return (0);
}

void	child_process(t_shell *shell, t_token *token, t_command *command)
{
	if (command->redirection == NULL)
	{
		dup2(shell->fd_pipe_in, STDIN_FILENO);
		if (command->next != NULL)
			dup2(shell->fd[1], STDOUT_FILENO);
		close(shell->fd[0]);
	}
	else
		pipe_redirection(shell, command);
	if (command->command_type == BINARY
		|| command->command_type == EXECUTABLE)
	{
		handle_pipe_bin(shell, token, command);
		clean_after_pipe(shell);
	}
	else
	{
		handle_pipe_builtin(shell, token, command);
		if (shell->fd_pipe_in != STDIN_FILENO)
			close(shell->fd_pipe_in);
		if (command->redirection != NULL)
			reset_fd(shell);
		clean_after_pipe(shell);
	}
}

void	clean_after_pipe(t_shell *shell)
{
	close(shell->fd[0]);
	close(shell->fd[1]);
	free_all(shell);
	exit(g_signal);
}

void	parent_process(pid_t pid, t_shell *shell)
{
	signal(SIGINT, handle_exec_signals);
	signal(SIGQUIT, handle_exec_signals);
	waitpid(pid, &g_signal, 0);
	g_signal = WEXITSTATUS(g_signal);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	close(shell->fd[1]);
	if (shell->fd_pipe_in != STDIN_FILENO)
		close(shell->fd_pipe_in);
	shell->fd_pipe_in = shell->fd[0];
}

void	pipe_redirection(t_shell *shell, t_command *command)
{
	if (create_file(command->redirection, shell, command) < 0)
		return ;
	initialize_redir(shell);
	if (shell->fd_in != 0)
		dup2(shell->fd_in, STDIN_FILENO);
	else
		dup2(shell->fd_pipe_in, STDIN_FILENO);
	if (command->next != NULL && shell->fd_out != 0)
		dup2(shell->fd_out, STDOUT_FILENO);
	else if (command->next != NULL && shell->fd_out == 0)
		dup2(shell->fd[1], STDOUT_FILENO);
	close(shell->fd[0]);
}
