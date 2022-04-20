/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:13:12 by llescure          #+#    #+#             */
/*   Updated: 2022/04/20 14:13:33 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (shell->pwd != NULL)
			free(shell->pwd);
		shell->pwd = ft_strdup(cwd);
		ft_putstr_fd(shell->pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	exit(g_signal);
}
