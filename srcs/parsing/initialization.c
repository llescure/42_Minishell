/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:01:06 by llescure          #+#    #+#             */
/*   Updated: 2022/04/07 08:01:09 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_struct(t_shell *shell, char **envp)
{
	get_env(shell, envp);
	if (g_signal == -1)
	{
		error_message(MALLOC, shell->fd_outfile);
		free_all(shell);
		return (g_signal);
	}
	shell->pwd = NULL;
	shell->fd_infile = STDIN_FILENO;
	shell->fd_outfile = STDOUT_FILENO;
	set_path(shell);
	return (0);
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
			if (rslt == NULL)
				g_signal = -1;
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

void	set_path(t_shell *shell)
{
	char	*temp;

	temp = find_word_in_tab(shell->env->env, "PATH");
	if (shell->path != NULL)
		free_tab(shell->path);
	if (temp != NULL)
	{
		shell->path = ft_split(temp, ':');
		free(temp);
	}
	else if (temp == NULL && g_signal == -1)
	{
		error_message(MALLOC, shell->fd_outfile);
		free_all(shell);
		return ;
	}
}

void	initialize_env_tab(t_shell *shell)
{
	shell->env->tab_variable_name = malloc(sizeof(char *)
			* (shell->env->index + 1));
	if (shell->env->tab_variable_name == NULL)
	{
		g_signal = -1;
		return ;
	}
	shell->env->tab_variable_equals = malloc(sizeof(char *)
			* (shell->env->index + 1));
	if (shell->env->tab_variable_name == NULL)
	{
		g_signal = -1;
		return ;
	}
}
