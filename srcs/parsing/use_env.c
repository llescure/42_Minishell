#include "../../include/minishell.h"

void get_env(t_env *env, char **envp)
{
    int index;
    //int i;

    index = 0;
    //i = 0;
    while (envp[index] != NULL)
        index++;
    env->index = index;
    env->env = envp;
	create_env_tab(env);
    //shell->env->alpha = envp;
   /* while (i < index)
    {
        if (ft_strncmp(envp[i], "HOME=", ft_strlen("HOME=")) == 0)
            get_absolute_path(shell, envp[i]);
        i++;
    }*/
}

void alpha_sort(t_shell *shell)
{
    int i;
    int j;
    char *temp;
    int size;

    i = 0;
    while (i < shell->env->index)
    {
        j = i + 1;
        while (j < shell->env->index)
        {
            size = ft_strlen(shell->env->alpha[i]) + ft_strlen(shell->env->alpha[j]);
            if (ft_strncmp(shell->env->alpha[i], shell->env->alpha[j], size) > 0)
            {
                temp = malloc(sizeof(char *) * ft_strlen(shell->env->alpha[i]) + 1);
                temp = shell->env->alpha[i];
                shell->env->alpha[i] = shell->env->alpha[j];
                shell->env->alpha[j] = temp;
            }
            j++;
        }
        i++;
    }
}

void get_absolute_path(t_shell *shell, char *path)
{
    int i;
    int j;

    i = 0;
    j = 0;
    shell->absolute_path = malloc(sizeof(char) * ft_strlen(path));
    while (path[i] != '\0' && path[i] != '=')
        i++;
    i++;
    while (path[i] != '\0')
    {
        shell->absolute_path[j] = path[i];
        i++;
        j++;
    }
    shell->absolute_path[j] = '\0';
}

void print_tab(char	**tab)
{
    int i;

    i = 0;
    while (tab[i] != NULL)
    {
        printf("tab[i]= %s$\n", tab[i]);
        i++;
    }
}

void	create_env_tab(t_env *env)
{
	int	i;

	env->tab_variable_name = malloc(sizeof(char *) * (env->index + 1));
	if (env->tab_variable_name == NULL)
	{
		g_signal = -1;
		return ;
	}
	env->tab_variable_equals = malloc(sizeof(char *) * (env->index + 1));
	if (env->tab_variable_name == NULL)
	{
		g_signal = -1;
		return ;
	}
	i = 0;
	while (i < env->index)
	{
		env->tab_variable_name[i] = ft_cut_str(env->env[i], 0,
						find_cara_in_word(env->env[i], '='));
		env->tab_variable_equals[i] = ft_strdup(ft_strrchr((const char *)env->env[i], '='));
		i++;
	}
	env->tab_variable_name[i] = NULL;
	env->tab_variable_equals[i] = NULL;
}
