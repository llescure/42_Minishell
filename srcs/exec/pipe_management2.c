/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 20:57:58 by llescure          #+#    #+#             */
/*   Updated: 2022/04/29 20:58:47 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_pipe_bin(t_shell *shell, t_token *token, t_command *command)
{
	if (shell->path != NULL)
	{
		free_tab(shell->path);
		shell->path = NULL;
	}
	set_path(shell);
	if (command->command_type == BINARY)
		execute_binary(shell, token, 0);
	else if (command->command_type == EXECUTABLE)
		execute_executable(shell, token);
}

void	handle_pipe_builtin(t_shell *shell, t_token *token, t_command *command)
{
	if (command->command_type == PWD)
		ft_pwd(shell);
	else if (command->command_type == ENV)
		print_env(shell->env->env);
	else if (command->command_type == EXIT)
		ft_exit(shell, token, command);
	else if (command->command_type == ECHO_CMD)
		ft_echo(token);
	else if (command->command_type == CD)
		ft_cd(shell, token, command);
	else if (command->command_type == EXPORT)
		ft_export(shell, token);
	else if (command->command_type == UNSET)
		ft_unset(shell, token);
}
