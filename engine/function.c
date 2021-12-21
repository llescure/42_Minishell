#include "minishell.h"

int get_absolute_path(t_shell *shell)
{
    int i;
    int compt;
    char cwd[PATH_MAX];

    compt = 0;
    i = 0;

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        shell->pwd = cwd;
    shell->absolute_path = malloc(sizeof(char) * ft_strlen(shell->pwd) + 1);
    if (!shell->absolute_path)
        ft_error(shell);
    while (shell->pwd[i] != '\0')
    {
        if (shell->pwd[i] == '/')
            compt++;
        if (compt == 3)
        {
            shell->absolute_path[i] = '\0';
            return (0);
        }
        shell->absolute_path[i] = shell->pwd[i];
        i++;
    }
    return (1);
}

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

void alpha_sort(t_shell *shell, int index)
{
    int i;
    int j;
    char *temp;

    i = 0;
    while (i < index)
    {
        j = i + 1;
        while (j < index)
        {
            if (ft_strncmp(shell->env[i], shell->env[j], ft_strlen(shell->env[i]) + ft_strlen(shell->env[j])) > 0)
            {
                temp = malloc(sizeof(char *) * ft_strlen(shell->env[i]) + 1);
                if (!temp)
                    ft_error(shell);
                temp = shell->env[i];
                shell->env[i] = shell->env[j];
                shell->env[j] = temp;
                // free(temp);
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < index)
    {
        printf("%s\n",shell->env[i]);
        i++;
    }
}

int ft_export(t_shell *shell, char **envp)
{
    int index;
    int i;

    index = 0;
    i = 0;
    while (envp[index])
    {
        // printf("%s\n", envp[index]);
        index++;
    }
    shell->env = malloc(sizeof(char*) * index + 1);
    if (!shell->env)
        ft_error(shell);
    while (i < index)
    {
        shell->env[i] = envp[i];
        i++;
    }
    alpha_sort(shell, index);
    return (0);
}
