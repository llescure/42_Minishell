#include "../../include/minishell.h"

int	ft_echo(char *str, char option)
{
	if (option != 'n' && option != 0)
	{
		printf("-%c", option);
	}
	printf("%s", str);
	if (option == 'n')
		return (0);
	else
		printf("\n");
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
	else
		ft_error(shell);
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
            printf("%s: No such file or directory\n", shell->str);
            ft_error(shell);
        }
        else
            return (0);
    }
    return (0);
}


void get_env(t_shell *shell, char **envp)
{
    int index;
    int i;

    index = 0;
    i = 0;
    while (envp[index])
        index++;
    shell->env->index = index;
    shell->env->env = malloc(sizeof(char*) * index + 1);
    if (!shell->env->env)
        ft_error(shell);
    shell->env->alpha = malloc(sizeof(char*) * index + 1);
    if (!shell->env->alpha)
        ft_error(shell);
    while (i < index)
    {
        shell->env->env[i] = envp[i];
        shell->env->alpha[i] = envp[i];
        if (ft_strncmp(envp[i], "HOME=", ft_strlen("HOME=")) == 0)
            get_absolute_path(shell, envp[i]);
        i++;
    }
}

int ft_export(t_shell *shell)
{
    alpha_sort(shell);
    print_env(shell, shell->env->alpha);
    return (0);
}
