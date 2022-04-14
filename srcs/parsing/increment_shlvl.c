/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:55:13 by llescure          #+#    #+#             */
/*   Updated: 2022/04/13 21:56:02 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	modify_shlvl(t_shell *shell)
{
	char	*shlvl;
	char	*level;
	char	*temp;

	if (shell->env->index == 0)
		return ;
	shlvl = ft_strdup("SHLVL=");
	level = ft_itoa(shell->shlvl);
	temp = shlvl;
	shlvl = ft_strjoin(temp, level);
	free(temp);
	free(level);
	delete_env_variable(shell, "SHLVL");
	add_new_env_variable(shlvl, shell);
}

char	*find_variable_value_env(t_shell *shell, char *value_to_find)
{
	int	i;

	i = 0;
	while (i < shell->env->index)
	{
		if (ft_strncmp(shell->env->tab_variable_name[i], value_to_find,
				ft_strlen(value_to_find)) == 0)
			return (shell->env->tab_variable_equals[i]);
		i++;
	}
	return (NULL);
}
