/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:48:52 by llescure          #+#    #+#             */
/*   Updated: 2022/04/20 14:15:04 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	execute_executable(t_shell *shell, t_token *token)
{
	char	**command;

	command = create_binary(token);
	if (double_ft_strncmp(command[0], "./minishell") == 1)
	{
		shell->shlvl++;
		modify_shlvl(shell);
	}
	if (command == NULL)
	{
		error_message(MALLOC, 0);
		exit(g_signal);
	}
	if (execve(command[0], command, shell->env->env) < 0)
	{
		error_message(COMMAND_ERROR, 1);
		free_tab(command);
		exit(g_signal);
	}
	free_tab(command);
}
