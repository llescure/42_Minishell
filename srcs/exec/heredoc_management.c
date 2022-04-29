/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:58:49 by llescure          #+#    #+#             */
/*   Updated: 2022/04/29 20:25:16 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_heredoc(char *file, t_shell *shell)
{
	int	fd[2];
	int	reader;

	if (pipe(fd) == -1)
		return (error_system(shell, PIPE_FORK));
	reader = fork();
	if (reader < 0)
		return (error_system(shell, PIPE_FORK));
	if (reader == 0)
	{
		new_line_until_delimitator(fd, file);
		close(fd[1]);
		free_all(shell);
		exit(g_signal);
	}
	else
	{
		waitpid(reader, &g_signal, 0);
		g_signal = WEXITSTATUS(g_signal);
		close(fd[1]);
		close(fd[0]);
	}
	return (0);
}

void	new_line_until_delimitator(int *fd, char *file)
{
	char	*line;

	close (fd[0]);
	ft_putstr_fd("> ", STDOUT_FILENO);
	while (get_next_line(STDIN_FILENO, &line, file) > 0)
	{
		if (ft_strncmp(line, file, ft_strlen(file)) == 0)
		{
			free(line);
			return ;
		}
		ft_putstr_fd("> ", STDOUT_FILENO);
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}
