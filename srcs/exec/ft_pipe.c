#include "../../include/minishell.h"

int	handle_pipe(t_shell *shell, t_command **command, t_token **token)
{
	int	fd[2];

	if (pipe(fd) < 0)
		return (error_system(shell, PIPE_FORK));
	while ((*command)->next != NULL)
	{
		child_process(shell, *command, *token, fd);
		*command = (*command)->next;
		while ((*token)->id < (*command)->id && *command != NULL)
			*token = (*token)->next;
	}
	handle_command(shell, *token, *command);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	child_process(t_shell *shell, t_command *command, t_token *token, int *fd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (error_system(shell, PIPE_FORK));
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (command->command_type == BINARY
				|| command->command_type == EXECUTABLE)
			handle_pipe_bin(shell, token, command);
		else
		{
			handle_pipe_builtin(shell, token, command);
			exit(g_signal);
		}
	}
	else
	{
		signal(SIGINT, handle_exec_signals);
		signal(SIGQUIT, handle_exec_signals);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &g_signal, 0);
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, handle_signals);
	}
	return (0);
}

void	handle_pipe_builtin(t_shell *shell, t_token *token, t_command *command)
{
	if (command->command_type == PWD)
		ft_pwd(shell);
	else if (command->command_type == ENV)
		print_env(shell->env->env);
	else if (command->command_type == EXIT)
		ft_exit(shell, token);
	else if (command->command_type == ECHO_CMD)
		ft_echo(token);
	else if (command->command_type == CD)
		ft_cd(shell, token);
	else if (command->command_type == EXPORT)
		ft_export(shell, token);
	else if (command->command_type == UNSET)
		ft_unset(shell, token);
}


void	handle_pipe_bin(t_shell *shell, t_token *token, t_command *command)
{
	if (command->command_type == BINARY)
		execute_binary(shell, token);
	else if (command->command_type == EXECUTABLE)
		execute_executable(shell, token);
}
