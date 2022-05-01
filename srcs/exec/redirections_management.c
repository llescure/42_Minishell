/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:49:00 by llescure          #+#    #+#             */
/*   Updated: 2022/05/01 18:55:24 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redirection(t_command *command, t_shell *shell, t_token *token)
{
	if (create_file(command->redirection, shell, command) < 0)
		return ;
	initialize_redir(shell);
	handle_command(shell, token, command);
	reset_fd(shell);
}

int	create_file(t_redirection *redirection, t_shell *shell, t_command *command)
{
	while (redirection != NULL)
	{
		if (redirection->type == REDIR_RIGHT
			|| redirection->type == D_REDIR_RIGHT
			|| redirection->type == REDIR_LEFT)
			open_fd(shell, redirection);
		else if (redirection->type == HEREDOC)
		{
			if (handle_heredoc(redirection, shell, command) < 0)
				return (g_signal);
		}
		redirection = redirection->next;
	}
	if (shell->fd_in == -1 || shell->fd_out == -1)
	{
		error_message(FILES, 1);
		return (-1);
	}
	return (0);
}

int	initialize_redir(t_shell *shell)
{
	if (shell->fd_in != 0)
	{
		shell->save_infile = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		dup2(shell->fd_in, STDIN_FILENO);
	}
	if (shell->fd_out != 0)
	{
		shell->save_outfile = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		dup2(shell->fd_out, STDOUT_FILENO);
	}
	return (0);
}

void	reset_fd(t_shell *shell)
{
	if (shell->fd_in > 0)
	{
		dup2(shell->save_infile, STDIN_FILENO);
		close(shell->fd_in);
		shell->fd_in = 0;
		close(shell->save_infile);
	}
	if (shell->fd_out > 0)
	{
		dup2(shell->save_outfile, STDOUT_FILENO);
		close(shell->fd_out);
		shell->fd_out = 0;
		close(shell->save_outfile);
	}
}

void	open_fd(t_shell *shell, t_redirection *redirection)
{
	if (redirection->type == REDIR_RIGHT)
	{
		if (shell->fd_out > 0)
			close(shell->fd_out);
		shell->fd_out = open(redirection->file, O_WRONLY | O_CREAT
				| O_TRUNC, 0777);
	}
	else if (redirection->type == D_REDIR_RIGHT)
	{
		if (shell->fd_out > 0)
			close(shell->fd_out);
		shell->fd_out = open(redirection->file, O_WRONLY | O_CREAT
				| O_APPEND, 0777);
	}
	else if (redirection->type == REDIR_LEFT)
	{
		if (shell->fd_in > 0)
			close(shell->fd_in);
		shell->fd_in = open(redirection->file, O_RDONLY);
	}
}
