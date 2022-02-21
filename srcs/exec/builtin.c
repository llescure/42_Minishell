#include "../../include/minishell.h"

void	ft_echo(t_shell *shell, int *compt)
{
	while (shell->token != NULL && shell->type != NULL)
	{
		if (ft_strncmp(shell->type->content, "command_option",
				ft_strlen("command_option")) == 0
				&& ft_strncmp(shell->type->content, "n", ft_strlen("n")) == 0)
		{
			error_message("command_option");
			return ;
		}
		while ((ft_strncmp(shell->type->content, "word", ft_strlen("word")) == 0
			|| ft_strncmp(shell->type->content, "white_space", ft_strlen("word")) == 0)
			&& shell->token != NULL && shell->type != NULL)
			{
				ft_putstr_fd(shell->token->content, shell
				shell->token = shell->token->next;
				shell->type = shell->type->next;
				*compt++;
			}
		else
			ft_putstr_fd("\n");
		shell->token = shell->token->next;
		shell->type = shell->type->next;
		*compt++;
	}
	return (0);
}

void ft_pwd(t_shell *shell)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		shell->pwd = cwd;
		printf("%s\n", shell->pwd);
	}
}

int ft_cd(t_shell *shell)
{
	if (shell->str == NULL)
	{
		chdir(shell->absolute_path);
		return (0);
	}
	else
	{
		if (chdir(shell->str) == -1)
		{
			error_message("file");
			return (g_signal);
		}
		else
			return (0);
	}
	return (0);
}

int ft_export(t_shell *shell)
{
	//alpha_sort(shell);
	print_tab(shell->env->env);
	return (0);
}
