/*#include "../../include/minishell.h"

int		execute_input(t_shell *shell, t_type *type, t_double_list *token,
		t_command *command)
{
	while (token != NULL && type != NULL)
	{
		if (type->content == COMMAND)
		{
			handle_builtin(shell, type, token, command);
			command = command->next;
			shell->command_count++;
		}
		token = token->next;
		type = type->next;
	}
	return (0);
}

void	handle_builtin(t_shell *shell, t_type *type, t_double_list *token,
		t_command *command)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
		execute_child_process(shell, type, token, command);
	else
	{
		signal(SIGINT, handle_exec_signals);
		signal(SIGQUIT, handle_exec_signals);
		waitpid(pid, &g_signal, 0);
		if (command->command_type == EXIT)
			ft_exit(shell, type, token, command);
		else if (command->command_type == CD)
			ft_cd(shell, type, token, command);
		else if (command->command_type == EXPORT)
			ft_export(shell, type, token, command);
		else if (command->command_type == UNSET)
			ft_unset(shell, type, token, command);
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, handle_signals);
	}
}

void	execute_child_process(t_shell *shell, t_type *type,
		t_double_list *token, t_command *command)
{
	if (command->command_type == ECHO_CMD)
		ft_echo(shell, type, token, command);
	else if (command->command_type == PWD )
		ft_pwd(shell, type, token, command);
	else if (command->command_type == EXIT || command->command_type == CD
			|| command->command_type == EXPORT
			|| command->command_type == UNSET)
		exit(g_signal);
	else if (command->command_type == ENV)
	{
		print_tab(shell->env->env);
		exit(g_signal);
	}
	else
		execute_binary(shell, type, token, command);
}*/
