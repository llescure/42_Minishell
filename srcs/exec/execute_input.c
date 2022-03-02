#include "../../include/minishell.h"

int		execute_input(t_shell *shell, char *user_input)
{
	if (user_input[0] == '\0')
		return (0);
	shell->i = 0;
	while (shell->token_bis[shell->i] != NULL)
	{
		if (ft_strncmp(shell->token_bis[shell->i], "redir_right",
					ft_strlen("redir_rigjt") == 0))

		{
			if (open_infile_redirection(shell) != 0)
				return (g_signal);
		}
		else if (ft_strncmp(shell->type_bis[shell->i], "redir_left",
					ft_strlen("redir_left")) == 0
			|| ft_strncmp(shell->type_bis[shell->i], "d_redir_right",
				ft_strlen("d_redir_right")) == 0)
		{
			if (open_infile_redirection(shell) != 0)
				return (g_signal);
		}
		else if (ft_strncmp(shell->type_bis[shell->i], "command",
					ft_strlen("command")) == 0 && (shell->command_count == 0
					|| look_for_word_in_type(shell->type, "pipe") == 1))
		{
			handle_builtin(shell, shell->token_bis[shell->i]);
			shell->command_count++;
		}
		if (shell->token_bis[shell->i] == NULL)
			break;
		shell->i++;
	}
	return (0);
}

void	handle_builtin(t_shell *shell, char *str)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
		execute_child_process(shell, str);
	else
	{
		signal(SIGINT, handle_exec_signals);
		signal(SIGQUIT, handle_exec_signals);
		waitpid(pid, &g_signal, 0);
		if (ft_strncmp(shell->token_bis[shell->i], "exit",
					ft_strlen("exit")) == 0)
			ft_exit(shell);
		else if (ft_strncmp(shell->token_bis[shell->i], "cd",
					ft_strlen("cd")) == 0)
			ft_cd(shell);
		else if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
			ft_export(shell);
		else if (ft_strncmp(str, "unset", ft_strlen("unset")) == 0)
			ft_unset(shell);
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, handle_signals);
	}
}

void	execute_child_process(t_shell *shell, char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen("echo")) == 0)
		ft_echo(shell);
	else if (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0)
		ft_pwd(shell);
	else if (ft_strncmp(str, "exit", ft_strlen("exit")) == 0
			|| ft_strncmp(str, "cd", ft_strlen("cd")) == 0
			|| ft_strncmp(str, "export", ft_strlen("export")) == 0
			|| ft_strncmp(str, "unset", ft_strlen("unset")) == 0)
		exit(g_signal);
	else if (ft_strncmp(str, "env", ft_strlen("env")) == 0)
	{
		print_tab(shell->env->env);
		exit(g_signal);
	}
	else
		execute_binary(shell);
}
