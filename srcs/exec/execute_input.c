#include "../../include/minishell.h"

int		execute_input(t_shell *shell)
{
	int	fd_infile;
	int	fd_outfile;
	char	*str;

	fd_infile = STDIN_FILENO;
	fd_outfile = STDOUT_FILENO;
	while (shell->token->next != NULL && shell->type->next != NULL)
	{
		str = shell->token->content;
		if (ft_strncmp(str, "command", ft_strlen("command")) == 0)
			handle_builtin(str, shell);
		else if (ft_isredirections(str[0]) == 1)
			if (open_file_redirections(shell, &fd_infile, &fd_outfile) != 0)
				return (g_signal);
		shell->token = shell->token->next;
		shell->type = shell->type->next;
	}
	str = shell->token->content;
	if (ft_strncmp(str, "command", ft_strlen("command")) == 0)
		handle_builtin(str, shell);
	else if (ft_isredirections(str[0]) == 1)
		if (open_file_redirection(shell, &fd_infile, &fd_outfile) != 0)
			return (g_signal);
	while (shell->token->previous != NULL && shell->token->previous != NULL)
	{
		shell->token = shell->token->previous;
		shell->type = shell->type->previous;
	}
	return (0);
}

void	handle_builtin(char *str, t_shell *shell)
{
	if (ft_strncmp(str, "exit", ft_strlen("exit") == 0))
		quit_program(shell);
	if (ft_strncmp(str, "echo", ft_strlen("echo")) == 0)
		ft_echo(str, shell);
	if (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0)
		ft_pwd(shell);
	if (ft_strncmp(str, "cd", ft_strlen("cd")) == 0)
		ft_cd(shell);
	if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
		ft_export(shell);
	if (ft_strchr(str, '=') != 0)
		create_variable(shell);
	//if (ft_strncmp(str, "env", ft_strlen("env")) == 0)
	//	print_env(shell);
}
