#include "../../include/minishell.h"

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
				ft_strlen(shell->env->tab_variable_name[i])) == 0
			&& ft_strncmp(new_env_variable, shell->env->tab_variable_name[i],
				ft_strlen(shell->env->tab_variable_name[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	export_without_argument(t_shell *shell, t_token *token)
{
	while (token != NULL && token->type == WHITE_SPACE)
		token = token->next;
	if (token == NULL)
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

void	print_tab(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

char	**export_tab(char **tab)
{
	char	*env;
	char	*temp;
	int		i;

	env = "export ";
	i = 0;
	while (tab[i] != NULL)
	{
		temp = tab[i];
		tab[i] = ft_strjoin(env, tab[i]);
		free(temp);
		i++;
	}
	return (tab);
}
