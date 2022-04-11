#include "../../include/minishell.h"

int	handle_redirection(t_redirection *redirection, t_shell *shell, int open_fd)
{
	int	in;
	int	out;

	in = 0;
	out = 0;
	if (redirection == NULL)
		return (0);
	while (redirection != NULL)
	{
		if (redirection->type == REDIR_RIGHT)
			out = open(redirection->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (redirection->type == D_REDIR_RIGHT)
			out = open(redirection->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else if (redirection->type == REDIR_LEFT)
			in = open(redirection->file, O_RDONLY);
		else if (redirection->type == HEREDOC)
		{
			if (handle_heredoc(redirection->file, shell) < 0)
				return (g_signal);
		}
		redirection = redirection->next;
	}
	if (in == -1 || out == -1)
	{
		error_message(FILES, 1);
		return (-1);
	}
	if (open_fd == 1)
	{
		if (open_file_descriptor(in, out, shell) < 0)
			return (-1);
	}
	return (0);
}

int	open_file_descriptor(int in, int out, t_shell *shell)
{
	if (in != 0)
	{
		shell->fd_infile = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != 0)
	{
		shell->fd_outfile = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	return (0);
}

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
		new_line_until_delimitator(fd, file);
	else
	{
		waitpid(reader, &g_signal, 0);
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
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (ft_strncmp(line, file, ft_strlen(file)) == 0)
		{
			free(line);
			exit(g_signal);
		}
		ft_putstr_fd("> ", STDOUT_FILENO);
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}
