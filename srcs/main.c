#include "../include/minishell.h"

void free_all(t_shell *shell)
{
	if (shell->path != NULL)
		free_tab(shell->path);
	if (shell->pwd != NULL)
		free(shell->pwd);
	rl_clear_history();
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void quit_program(t_shell *shell)
{
	free_all(shell);
	exit (0);
}

/*void	handle_builtin(t_shell *shell)
{
	if (ft_strncmp(*shell->cmd, "exit", ft_strlen("exit") == 0))
		quit_program(shell);
	if (ft_strncmp(*shell->cmd, "echo", ft_strlen("echo")) == 0)
	{
		ft_echo(shell->str, shell->option);
		quit_program(shell);
	}
	if (ft_strncmp(*shell->cmd, "pwd", ft_strlen("pwd")) == 0)
	{
		ft_pwd(shell);
		quit_program(shell);
	}
	if (ft_strncmp(*shell->cmd, "cd", ft_strlen("cd")) == 0)
	{
		ft_cd(shell);
		quit_program(shell);
	}
	if (ft_strncmp(*shell->cmd, "export", ft_strlen("export")) == 0)
	{
		ft_export(shell);
		quit_program(shell);
	}
		if (ft_strchr(shell->str, '=') != 0)
		{
		create_variable(shell);
		quit_program(shell);
		}
	if (ft_strncmp(*shell->cmd, "env", ft_strlen("env")) == 0)
	{
		print_env(shell);
		quit_program(shell);
	}
}*/

int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	g_signal = 0;
	shell.path = NULL;
	shell.pwd = NULL;
	if (ft_strncmp(argv[0], "./minishell", ft_strlen("./minishell")) != 0
			|| argc != 1)
	{
		error_message("parameters", &shell);
		return (g_signal);
	}
	if (init_struct(&shell, envp) < 0)
		return (g_signal);
	if (launch_shell(&shell) != 0)
		return (g_signal);
	return (0);
}
