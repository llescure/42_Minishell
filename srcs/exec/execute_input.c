#include "../../include/minishell.h"

int	execute_input(t_shell *shell, t_token *token, t_command *command)
{
	while (token != NULL)
	{
		if (token->type == COMMAND)
		{
			launch_command(shell, token, command);
			if (token == NULL)
				return (0);
			command = command->next;
			while (command != NULL && command->command_type == VOID)
				command = command->next;
			shell->command_count++;
		}
		token = token->next;
	}
	return (0);
}

void	launch_command(t_shell *shell, t_token *token, t_command *command)
{
	if (command->redirection != NULL)
		return (handle_redirection(command, shell, token));
//	if (command->pipe_input == 1 || command->pipe_output == 1)
//		return (handle_pipe(shell, command));
	handle_command(shell, token, command);
}

void	handle_command(t_shell *shell, t_token *token, t_command *command)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		if (shell->path != NULL)
			free_tab(shell->path);
		shell->path = NULL;
		execute_child_process(shell, token, command);
	}
	else
		execute_parent_process(shell, token, command, pid);
}

void	execute_child_process(t_shell *shell, t_token *token,
		t_command *command)
{
	if (command->command_type == PWD)
		ft_pwd(shell);
	else if (command->command_type == EXIT || command->command_type == CD
		|| command->command_type == EXPORT || command->command_type == ECHO_CMD
		|| command->command_type == UNSET || command->command_type == VOID)
		exit(g_signal);
	else if (command->command_type == ENV)
	{
		print_env(shell->env->env);
		exit(g_signal);
	}
	else if (command->command_type == BINARY)
		execute_binary(shell, token);
	else if (command->command_type == EXECUTABLE)
		execute_executable(shell, token);
}

void	execute_parent_process(t_shell *shell, t_token *token,
		t_command *command, int pid)
{
	signal(SIGINT, handle_exec_signals);
	signal(SIGQUIT, handle_exec_signals);
	waitpid(pid, &g_signal, 0);
	if (command->command_type == EXIT)
		ft_exit(shell, token);
	else if (command->command_type == ECHO_CMD)
		ft_echo(token);
	else if (command->command_type == CD)
		ft_cd(shell, token);
	else if (command->command_type == EXPORT)
		ft_export(shell, token);
	else if (command->command_type == UNSET)
		ft_unset(shell, token);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}
