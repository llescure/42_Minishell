/*#include "../../include/minishell.h"

void	ft_exit(t_shell *shell, t_type *type, t_double_list *token)
{
	type = type->next;
	token = token->next;
	exit_basic_case(shell, type, token);
	while (token != NULL && type->content != WHITE_SPACE)
	{
		token = token->next;
		type = type->next;
	}
	exit_basic_case(shell, type, token);
	if (is_number(token->content) == 1)
		g_signal = ft_atoi(token->content);
	else if (is_number(token->content) == 0)
	{
		ft_putstr_fd("exit\n", shell->fd_outfile);
		error_message(EXIT_ERROR, shell->fd_outfile);
		free_all(shell);
		exit(g_signal);
	}
	type = type->next;
	token = token->next;
	if (check_number_of_arguments(shell, type, token) != 0)
		exit(g_signal);
	free_all(shell);
	ft_putstr_fd("exit\n", shell->fd_outfile);
	exit(g_signal % 256);
}

void	exit_basic_case(t_shell *shell, t_type *type, t_double_list *token)
{
	if (token == NULL)
	{
		ft_putstr_fd("exit\n", shell->fd_outfile);
		free_all(shell);
		exit (g_signal);
	}
}

int	check_number_of_arguments(t_shell *shell, t_type *type,
		t_double_list *token)
{
	while (token != NULL)
	{
		if (type->content == WHITE_SPACE)
		{
			ft_putstr_fd("exit\n", shell->fd_outfile);
			error_message(ARGUMENTS, shell->fd_outfile);
			free_all(shell);
			return (g_signal);;
		}
		type = type->next;
		token = token->next;
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
		error_message(EXPORT_ERROR, shell->fd_outfile);
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
