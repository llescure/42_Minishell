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
			error_message("file");
			return (g_signal);
		}
        else
            return (0);
    }
    return (0);
}

int ft_export(t_shell *shell)
{
    //alpha_sort(shell);
    print_tab(shell->env->env);
    return (0);
}
