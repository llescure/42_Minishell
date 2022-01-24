#include "../../include/minishell.h"

void init_struct(t_shell *shell, char **envp)
{
	t_env	env;
	char	*temp;

	get_env(&env, envp);
	shell->env = &env;
	shell->pwd = malloc(sizeof(char) * PATH_MAX + 1);
	if (shell->pwd == NULL)
		ft_error(shell);
	temp = find_word_in_tab(shell->env->env, "PATH");
	if (temp != NULL)
	{
		shell->path = ft_split(temp, ':');
		free(temp);
	}
}

char	*find_word_in_tab(char **envp, char *to_find)
{
	int		i;
	char	*temp;
	char	*rslt;

	i = 0;
	while (envp[i] != NULL)
	{
		temp = ft_strnstr((const char *)envp[i], (const char *)to_find,
				ft_strlen(to_find));
		if (temp != NULL)
		{
			rslt = delete_until_cara(temp, ':');
			return (rslt);
		}
		i++;
	}
	return (NULL);
}

char	*delete_until_cara(char *str, int c)
{
	unsigned int	i;
	unsigned int	j;
	char			*temp;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (temp == NULL)
		return (NULL);
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (temp);
	i++;
	while (str[i] != '\0')
	{
		temp[j] = str[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	return (temp);
}
