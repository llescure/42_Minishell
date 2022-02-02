#include "../../include/minishell.h"

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

void print_env(t_shell *shell)
{
    int i;

    i = 0;
    while (i < shell->env->index)
    {
        printf("%s\n", shell->env->env[i]);
        i++;
    }
}
