/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:47:46 by llescure          #+#    #+#             */
/*   Updated: 2022/04/29 20:59:02 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_pipe(t_shell *shell, t_command *command, t_token *token)
{
	int		fd[2];
	pid_t	pid;

	shell->fd_pipe_in = STDIN_FILENO;
	while (command != NULL)
	{
		if (pipe(fd) < 0)
			return (error_system(shell, PIPE_FORK));
		pid = fork();
		if (pid < 0)
			return (error_system(shell, PIPE_FORK));
		else if (pid == 0)
			child_process(shell, token, command, fd);
		else
		{
			parent_process(pid, fd, shell);
			command = command->next;
			while (command != NULL && token != NULL && token->id < command->id)
				token = token->next;
		}
	}
	close(fd[1]);
	close(fd[0]);
	return (0);
}

void	child_process(t_shell *shell, t_token *token, t_command *command,
		int	*fd)
{
	if (command->redirection == NULL)
	{
		dup2(shell->fd_pipe_in, STDIN_FILENO);
		if (command->next != NULL)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
	}
	else
		pipe_redirection(shell, command, fd);
	if (command->command_type == BINARY
		|| command->command_type == EXECUTABLE)
	{
		handle_pipe_bin(shell, token, command);
		clean_after_pipe(shell, fd);
	}
	else
	{
		handle_pipe_builtin(shell, token, command);
		if (shell->fd_pipe_in != STDIN_FILENO)
			close(shell->fd_pipe_in);
		if (command->redirection != NULL)
			reset_fd(shell);
		clean_after_pipe(shell, fd);
	}
}

void	clean_after_pipe(t_shell *shell, int *fd)
{
	close(fd[0]);
	close(fd[1]);
	free_all(shell);
	exit(g_signal);
}

void	parent_process(pid_t pid, int *fd, t_shell *shell)
{
	signal(SIGINT, handle_exec_signals);
	signal(SIGQUIT, handle_exec_signals);
	waitpid(pid, &g_signal, 0);
	//ft_putstr_fd(ft_itoa(fd[1]), STDERR_FILENO);
	//ft_putstr_fd("\n", STDERR_FILENO);
	g_signal = WEXITSTATUS(g_signal);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	close(fd[1]);
	if (shell->fd_pipe_in != STDIN_FILENO)
		close(shell->fd_pipe_in);
	shell->fd_pipe_in = fd[0];
}

void	pipe_redirection(t_shell *shell, t_command *command, int *fd)
{
	if (create_file(command->redirection, shell) < 0)
		return ;
	initialize_redir(shell);
	if (shell->fd_in != 0)
		dup2(shell->fd_in, STDIN_FILENO);
	else
		dup2(shell->fd_pipe_in, STDIN_FILENO);
	if (command->next != NULL && shell->fd_out != 0)
		dup2(shell->fd_out, STDOUT_FILENO);
	else if (command->next != NULL && shell->fd_out == 0)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
}
