#include "../../include/minishell.h"

void	ft_export(t_shell *shell)
{
	shell->i++;
	if (export_without_argument(shell) == 1)
		return ;
	while (shell->token_bis[shell->i] != NULL
			&& (ft_strncmp(shell->type_bis[shell->i], "white_space",
					ft_strlen("white_space")) == 0
				|| ft_strncmp(shell->type_bis[shell->i], "word",
					ft_strlen("word")) == 0
				|| ft_strncmp(shell->type_bis[shell->i], "command",
					ft_strlen("command")) == 0
				|| ft_strncmp(shell->type_bis[shell->i], "equal",
					ft_strlen("equal")) == 0))
	{
		if (ft_strncmp(shell->type_bis[shell->i], "word",
					ft_strlen("word")) == 0
				|| ft_strncmp(shell->type_bis[shell->i], "command",
					ft_strlen("command")) == 0)
		{
			shell->i++;
			if (shell->token_bis[shell->i] == NULL)
				create_lonely_env_variable(shell);
			else if (ft_strncmp(shell->type_bis[shell->i], "white_space",
						ft_strlen("white_space")) == 0
				&& shell->token_bis[shell->i + 1] != NULL
				&& ft_strncmp(shell->type_bis[shell->i + 1], "equal",
						ft_strlen("equal")) == 0)
				error_message("export", shell->fd_outfile);
			else if (ft_strncmp(shell->type_bis[shell->i], "white_space",
						ft_strlen("white_space")) == 0)
				create_lonely_env_variable(shell);
			else if (ft_strncmp(shell->type_bis[shell->i], "equal",
						ft_strlen("equal")) == 0)
				create_new_env_variable(shell);
		}
		else if (ft_strncmp(shell->type_bis[shell->i], "equal",
					ft_strlen("equal")) == 0)
			error_message("export", shell->fd_outfile);
	}
}

void	create_lonely_env_variable(t_shell *shell)
{
	char	*new_env_variable;

	shell->i--;
	if (check_if_variable_already_exists(shell, shell->token_bis[shell->i])
		== 1)
		return ;
	new_env_variable = ft_strdup(shell->token_bis[shell->i]);
	add_new_env_variable(new_env_variable, shell);
}

void	create_new_env_variable(t_shell *shell)
{
	char	*new_env_variable;
	char	*temp;
	char	*str;

	shell->i--;
	new_env_variable = ft_strdup(shell->token_bis[shell->i]);
	shell->i++;
	while (shell->token_bis[shell->i] != NULL)
	{
		str = shell->type_bis[shell->i];
		if (ft_strncmp(str, "pipe", ft_strlen("pipe")) == 0
				|| ft_strncmp(str, "redir_left", ft_strlen("redir_left")) == 0
				|| ft_strncmp(str, "redir_right", ft_strlen("redir_right")) == 0
				|| ft_strncmp(str, "heredoc", ft_strlen("heredoc")) == 0
				|| ft_strncmp(str, "d_redir_right", ft_strlen("d_redir_right")) == 0)
			break;
		temp = new_env_variable;
		new_env_variable = ft_strjoin(new_env_variable,
				shell->token_bis[shell->i]);
		free(temp);
		shell->i++;
	}
	temp = ft_cut_str(new_env_variable, 0, find_cara_in_word(new_env_variable,
				'='));
	if (check_if_variable_already_exists(shell, temp) == 1)
		delete_env_variable(shell, temp);
	free(temp);
	add_new_env_variable(new_env_variable, shell);
}

void	add_new_env_variable(char *new_env_variable, t_shell *shell)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (shell->env->index + 2));
	if (new_env == NULL)
		return ;
	i = 0;
	while (shell->env->env[i] != NULL)
	{
		new_env[i] = ft_strdup(shell->env->env[i]);
		i++;
	}
	new_env[i] = new_env_variable;
	i++;
	new_env[i] = NULL;
	free_tab(shell->env->env);
	shell->env->env = new_env;
	shell->env->index++;
	free_tab(shell->env->tab_variable_name);
	free_tab(shell->env->tab_variable_equals);
	create_env_tab(shell);
}

int	check_if_variable_already_exists(t_shell *shell, char *new_env_variable)
{
	int	i;

	i = 0;
	while (shell->env->tab_variable_name[i] != NULL)
	{
		if (ft_strncmp(new_env_variable, shell->env->tab_variable_name[i],
					ft_strlen(shell->env->tab_variable_name[i])) == 0 &&
				ft_strncmp(new_env_variable, shell->env->tab_variable_name[i],
					ft_strlen(shell->env->tab_variable_name[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	export_without_argument(t_shell *shell)
{
	while (shell->token_bis[shell->i] != NULL
			&& ft_strncmp(shell->type_bis[shell->i], "white_space",
					ft_strlen("white_space")) == 0)
		shell->i++;
	if (shell->token_bis[shell->i] == NULL)
	{
		if (shell->env->alpha != NULL)
			free_tab(shell->env->alpha);
		shell->env->alpha = copy_tab(shell->env->env, shell->env->index);
		alpha_sort(shell);
		shell->env->alpha = export_tab(shell->env->alpha);
		print_tab(shell->env->alpha);
		return (1);
	}
	return (0);
}
