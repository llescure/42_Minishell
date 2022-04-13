#include "../../include/minishell.h"

void	ft_unset(t_shell *shell, t_token *token)
{
	token = token->next;
	while (token != NULL && (token->type == WHITE_SPACE
			|| token->type == WORD || token->type == COMMAND))
	{
		if (token->type == WORD || token->type == COMMAND)
		{
			if (check_if_variable_already_exists(shell, token->content) == 1)
				delete_env_variable(shell, token->content);
		}
		token = token->next;
	}
	if (token != NULL && token->type == EQUAL)
		error_message(EXPORT_ERROR, 1);
}

void	delete_env_variable(t_shell *shell, char *env_to_delete)
{
	char	**new_env;

	new_env = copy_previous_env_variable(shell, env_to_delete);
	free_tab(shell->env->env);
	shell->env->env = new_env;
	shell->env->index--;
	free_tab(shell->env->tab_variable_name);
	free_tab(shell->env->tab_variable_equals);
	if (shell->path != NULL)
		free_tab(shell->path);
	shell->path = NULL;
	create_env_tab(shell);
}

char	**copy_previous_env_variable(t_shell *shell, char *env_to_delete)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * shell->env->index);
	while (j < shell->env->index - 1)
	{
		if (ft_strncmp(shell->env->tab_variable_name[i], env_to_delete,
				ft_strlen(env_to_delete)) == 0
			&& ft_strncmp(shell->env->tab_variable_name[i], env_to_delete,
				ft_strlen(shell->env->tab_variable_name[i])) == 0)
			i++;
		new_env[j] = ft_strdup(shell->env->env[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}
