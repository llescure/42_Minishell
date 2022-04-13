#include "../../include/minishell.h"

void	ft_pipe_out(t_shell *shell)
{
	shell->ofd_out = dup(STDOUT_FILENO);
	close (STDOUT_FILENO);
	unlink(shell->path_out);
	open(shell->path_out, O_CREAT, 00777);
	 shell->fd_out = open(shell->path_out, O_RDWR);
	dup2(shell->fd_out, STDOUT_FILENO);
	close (shell->fd_out);
}

void	ft_copy_fd(int fd_s, int fd_d)
{
	char	buff[2];

//	printf ("STDERR_FILENO : '%d'\n", g_signal);
	while(read(fd_s, buff, 1) > 0)
	{
		//printf ("STDERR_FILENO : '%d'\n", g_signal);
		if (g_signal != 0)
			write(1, buff, 1);
		write(fd_d, buff, 1);
	}
}

void	ft_pipe_in(t_shell *shell)
{
	int		out;
	

	shell->ofd_in = dup(STDIN_FILENO);
	close (STDIN_FILENO);
	out = open(shell->path_out, O_RDWR);
	unlink(shell->path_in);
	open(shell->path_in, O_CREAT, 00777);
	shell->fd_in = open(shell->path_in, O_RDWR);
	ft_copy_fd(out, shell->fd_in);
	close (out);
	close (shell->fd_in);
	shell->fd_in = open(shell->path_in, O_RDWR);
	dup2(shell->fd_in, STDIN_FILENO);
}

void	ft_pipe_close_fd(t_shell *shell, t_command *cmd)
{
	if (cmd->pipe_output == 1)
		dup2(shell->ofd_in, STDIN_FILENO);
	if (cmd->pipe_input == 1)
		dup2(shell->ofd_out, STDOUT_FILENO);
}
