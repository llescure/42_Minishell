#include "minishell.h"

void init_struct(t_shell *shell, char **envp)
{
	shell->pwd = malloc(sizeof(char) * PATH_MAX + 1);
	if (!shell->pwd)
		ft_error(shell);
	shell->option = 0;
	shell->str = NULL;
	get_env(shell, envp);
	shell->variables = NULL;
}

void free_all(t_shell *shell)
{
	int i;

	i = 0;
	if (shell->absolute_path)
		free(shell->absolute_path);
//	if (shell->variables)
//		ft_lstclear(&shell->variables, 0);
	// if (shell->cmd)
		// free (shell->cmd);
	// if (shell->str)
		// free (shell->str);
}

void ft_error(t_shell *shell)
{
	printf("ERROR\n");
	free_all(shell);
	exit (-1);
}

void quit_program(t_shell *shell)
{
	free_all(shell);
	exit (0);
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	init_struct(&shell, envp);
	shell.cmd = "export";
	if (argc != 1)
		ft_error(&shell);
	if (argv[0])
	if (ft_strncmp(shell.cmd, "exit", ft_strlen("exit") == 0))
		quit_program(&shell);
	if (ft_strncmp(shell.cmd, "echo", ft_strlen("echo")) == 0)
	{
		ft_echo(shell.str, shell.option);
		quit_program(&shell);
	}
	if (ft_strncmp(shell.cmd, "pwd", ft_strlen("pwd")) == 0)
	{
		ft_pwd(&shell);
		quit_program(&shell);
	}
	if (ft_strncmp(shell.cmd, "cd", ft_strlen("cd")) == 0)
	{
		ft_cd(&shell);
		ft_pwd(&shell);
		quit_program(&shell);
	}
	if (ft_strncmp(shell.cmd, "export", ft_strlen("export")) == 0)
	{
		ft_export(&shell);
		quit_program(&shell);
	}
/*		if (ft_strchr(shell.str, '=') != 0)
		{
			create_variable(&shell);
			quit_program(&shell);
		}
*/
	if (ft_strncmp(shell.cmd, "env", ft_strlen("env")) == 0)
	{
		print_env(&shell, shell.env.env);
		quit_program(&shell);

	}
	while (1)
		pause();
	return (0);
}
