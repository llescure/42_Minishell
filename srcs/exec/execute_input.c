#include "../../include/minishell.h"

int		execute_input(t_shell *shell, char *user_input)
{
	if (user_input[0] == '\0')
		return (0);
	shell->i = 0;
	while (shell->token_bis[shell->i] != NULL)
	{
		if (ft_strncmp(shell->type_bis[shell->i], "command",
				ft_strlen("command")) == 0)
			handle_builtin(shell, shell->token_bis[shell->i]);
		else if (ft_strncmp(shell->type_bis[shell->i], "redir_right",
					ft_strlen("redir_right")) == 0
				|| ft_strncmp(shell->type_bis[shell->i], "redir_left",
					ft_strlen("redir_left")) == 0
				|| ft_strncmp(shell->type_bis[shell->i], "d_redir_right",
					ft_strlen("d_redir_left")) == 0)

		{
			if (open_file_redirection(shell) != 0)
				return (g_signal);
		}
		if (shell->token_bis[shell->i] == NULL)
			break;
		shell->i++;
	}
	return (0);
}

void	handle_builtin(t_shell *shell, char *str)
{
	if (ft_strncmp(str, "exit", ft_strlen("exit")) == 0)
		ft_exit(shell);
	else if (ft_strncmp(str, "echo", ft_strlen("echo")) == 0)
		ft_echo(shell);
	else if (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0)
		ft_pwd(shell);
	else if (ft_strncmp(str, "cd", ft_strlen("cd")) == 0)
		ft_cd(shell);
	else if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
		ft_export(shell);
	else if (ft_strncmp(str, "env", ft_strlen("env")) == 0)
		print_tab(shell->env->env);
	else if (ft_strncmp(str, "unset", ft_strlen("unset")) == 0)
		ft_unset(shell);
}
