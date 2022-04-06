#include "../../include/minishell.h"

int		execute_input(t_shell *shell, t_token *token, t_command *command)
{
	while (token != NULL)
	{
		if (token->type == COMMAND)
		{
			handle_builtin(shell, &token, command);
			if (token == NULL)
				return (0);
			command = command->next;
			shell->command_count++;
		}
		token = token->next;
	}
	return (0);
}

void	handle_builtin(t_shell *shell, t_token **token, t_command *command)
{
	int	pid;

//	handle_pipe(shell, command);
	if (handle_redirection(command->redirection, shell) < 0)
		return;
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
		execute_child_process(shell, *token, command);
	else
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
	dup2(shell->fd_infile, STDIN_FILENO);
	dup2(shell->fd_outfile, STDOUT_FILENO);
}

void	execute_child_process(t_shell *shell, t_token *token,
		t_command *command)
{
	if (command->command_type == PWD )
		ft_pwd(shell);
	else if (command->command_type == EXIT || command->command_type == CD
		|| command->command_type == EXPORT || command->command_type == ECHO_CMD
		|| command->command_type == UNSET)
		exit(g_signal);
	else if (command->command_type == ENV)
	{
		print_tab(shell->env->env);
		exit(g_signal);
	}
	else if (command->command_type == EXECUTABLE)
		execute_executable(shell, token);
	else
		execute_binary(shell, token);
}

/*void	handle_pipe(t_shell *shell, t_command *command)
{
	if (pipe_input == 1)
	if (pipe_output == 1)
}*/
