/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:49:00 by llescure          #+#    #+#             */
/*   Updated: 2022/04/22 10:08:48 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redirection(t_command *command, t_shell *shell, t_token *token)
{
	int	save_infile;
	int	save_outfile;

	save_infile = -1;
	save_outfile = -1;
	if (create_file(command->redirection, shell) < 0)
		return ;
	initialize_redir(shell, &save_infile, &save_outfile);
	handle_command(shell, token, command);
	reset_fd(shell, &save_infile, &save_outfile);
}

int	create_file(t_redirection *redirection, t_shell *shell)
{
	while (redirection != NULL)
	{
		if (redirection->type == REDIR_RIGHT)
			shell->fd_out = open(redirection->file, O_WRONLY | O_CREAT
					| O_TRUNC, 0777);
		else if (redirection->type == D_REDIR_RIGHT)
			shell->fd_out = open(redirection->file, O_WRONLY | O_CREAT
					| O_APPEND, 0777);
		else if (redirection->type == REDIR_LEFT)
			shell->fd_in = open(redirection->file, O_RDONLY);
		else if (redirection->type == HEREDOC)
		{
			if (handle_heredoc(redirection->file, shell) < 0)
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

int	initialize_redir(t_shell *shell, int *save_infile, int *save_outfile)
{
	if (shell->fd_in != 0)
	{
		*save_infile = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		dup2(shell->fd_in, STDIN_FILENO);
	}
	if (shell->fd_out != 0)
	{
		*save_outfile = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		dup2(shell->fd_out, STDOUT_FILENO);
	}
	return (0);
}

void	reset_fd(t_shell *shell, int *save_infile, int *save_outfile)
{
	if (shell->fd_in != 0)
	{
		dup2(*save_infile, STDIN_FILENO);
		close(shell->fd_in);
		shell->fd_in = 0;
		close(*save_infile);
	}
	if (shell->fd_out != 0)
	{
		dup2(*save_outfile, STDOUT_FILENO);
		close(shell->fd_out);
		shell->fd_out = 0;
		close(*save_outfile);
	}
}
