#include "../include/minishell.h"

void free_all(t_shell *shell)
{
	if (shell->path != NULL)
		free_tab(shell->path);
	if (shell->pwd != NULL)
		free(shell->pwd);
	if (shell->env->tab_variable_name != NULL)
		free_tab(shell->env->tab_variable_name);
	if (shell->env->env != NULL)
		free_tab(shell->env->env);
	if (shell->env->alpha != NULL)
		free_tab(shell->env->alpha);
	if (shell->absolute_path != NULL)
		free(shell->absolute_path);
	if (shell->env->tab_variable_equals != NULL)
		free_tab(shell->env->tab_variable_equals);
	if (shell->token != NULL)
		ft_double_free_list(&shell->token, 1);
	if (shell->type != NULL)
		ft_double_free_list(&shell->type, 0);
	if (shell->token_bis != NULL)
		free_tab(shell->token_bis);
	if (shell->type_bis != NULL)
		free_tab(shell->type_bis);
	rl_clear_history();
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	if (tab != NULL)
		free(tab);
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	t_env	env;

	g_signal = 0;
	shell.path = NULL;
	shell.pwd = NULL;
	shell.env = &env;
	shell.env->tab_variable_name = NULL;
	shell.env->tab_variable_equals = NULL;
	if (ft_strncmp(argv[0], "./minishell", ft_strlen("./minishell")) != 0
			|| argc != 1)
	{
		error_message("parameters", 1);
		free_all(&shell);
		return (g_signal);
	}
	if (init_struct(&shell, envp) < 0)
		return (g_signal);
	if (launch_shell(&shell) != 0)
		return (g_signal);
	return (0);
}
