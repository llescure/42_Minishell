#include "../../include/minishell.h"

/*void	ft_exit(t_shell *shell)
{
	shell->i++;
	exit_basic_case(shell);
	while (shell->token_bis[shell->i] != NULL &&
			ft_strncmp(shell->type_bis[shell->i], "white_space",
				ft_strlen("white_space")) == 0)
		shell->i++;
	exit_basic_case(shell);
	if (is_number(shell->token_bis[shell->i]) == 1)
		g_signal = ft_atoi(shell->token_bis[shell->i]);
	else if (is_number(shell->token_bis[shell->i]) == 0)
	{
		ft_putstr_fd("exit\n", shell->fd_outfile);
		error_message(EXIT, shell->fd_outfile);
		free_all(shell);
		exit(g_signal);
	}
	shell->i++;
	if (check_number_of_arguments(shell) != 0)
		exit(g_signal);
	free_all(shell);
	ft_putstr_fd("exit\n", shell->fd_outfile);
	exit(g_signal % 256);
}

void	exit_basic_case(t_shell *shell)
{
	if (shell->token_bis[shell->i] == NULL)
	{
		ft_putstr_fd("exit\n", shell->fd_outfile);
		free_all(shell);
		exit (g_signal);
	}
}

int	check_number_of_arguments(t_shell *shell)
{
	while (shell->token_bis[shell->i] != NULL)
	{
		if (ft_strncmp(shell->type_bis[shell->i], "white_space",
					ft_strlen("white_space")) != 0)
		{
			ft_putstr_fd("exit\n", shell->fd_outfile);
			error_message(ARGUMENTS, shell->fd_outfile);
			free_all(shell);
			return (g_signal);;
		}
		shell->i++;
	}
	return (0);
}

void	ft_unset(t_shell *shell)
{
	char	*str;

	shell->i++;
	while (shell->token_bis[shell->i] != NULL
		   	&& (ft_strncmp(shell->type_bis[shell->i], "white_space",
				ft_strlen("white_space")) == 0
			|| ft_strncmp(shell->type_bis[shell->i], "word",
				ft_strlen("word")) == 0
			|| ft_strncmp(shell->type_bis[shell->i], "command",
				ft_strlen("command")) == 0))
	{
		str = shell->type_bis[shell->i];
		if (ft_strncmp(str, "word", ft_strlen("word")) == 0 ||
	   		ft_strncmp(str, "command", ft_strlen("command")) == 0)
		{
			if (check_if_variable_already_exists(shell,
				shell->token_bis[shell->i]) == 1)
				delete_env_variable(shell, shell->token_bis[shell->i]);
		}
		shell->i++;
	}
	if (shell->token_bis[shell->i] != NULL
		&& ft_strncmp(shell->type_bis[shell->i], "equal",
		ft_strlen("equal")) == 0)
		error_message(EXPORT, shell->fd_outfile);
}

void	delete_env_variable(t_shell *shell, char *env_to_delete)
{
	int	i;
	int	j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * shell->env->index);
	while (j < shell->env->index - 1)
	{
		if (ft_strncmp(shell->env->tab_variable_name[i], env_to_delete,
				ft_strlen(env_to_delete)) == 0 &&
				ft_strncmp(shell->env->tab_variable_name[i], env_to_delete,
				ft_strlen(shell->env->tab_variable_name[i])) == 0)
			i++;
		new_env[j] = ft_strdup(shell->env->env[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	free_tab(shell->env->env);
	shell->env->env = new_env;
	shell->env->index--;
	free_tab(shell->env->tab_variable_name);
	free_tab(shell->env->tab_variable_equals);
	if (shell->path != NULL)
		free_tab(shell->path);
	shell->path = NULL;
	create_env_tab(shell);
}*/
