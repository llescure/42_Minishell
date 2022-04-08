#include "../../include/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (shell->pwd != NULL)
			free(shell->pwd);
		shell->pwd = ft_strdup(cwd);
		ft_putstr_fd(shell->pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	exit(g_signal);
}

void	ft_cd(t_shell *shell, t_token **token)
{
	int	return_value;

	*token = (*token)->next;
	while (*token != NULL && (*token)->type == WHITE_SPACE)
		*token = (*token)->next;
	if (*token == NULL)
	{
		chdir(shell->absolute_path);
		return ;
	}
	return_value = chdir((*token)->content);
	if (return_value == -1)
		error_message(FILES, 1);
}

void	execute_executable(t_shell *shell, t_token *token)
{
	char	**command;

	command = create_binary(token);
	if (double_ft_strncmp(command[0], "./minishell") == 1)
	{
		shell->shlvl++;
		modify_shlvl(shell);
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, handle_signals);
	}
	if (command == NULL)
	{
		error_message(MALLOC, 0);
		return ;
	}
	if (execve(command[0], command, shell->env->env) < 0)
	{
		error_message(COMMAND_ERROR, 1);
		free_tab(command);
		return ;
	}
	free_tab(command);
}
