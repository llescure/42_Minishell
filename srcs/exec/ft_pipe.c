#include "../../include/minishell.h"

int	handle_pipe(t_shell *shell, t_command **command, t_token **token)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) < 0)
		return (error_system(shell, PIPE_FORK));
	if ((*command) != NULL)
	{
		pid = fork();
		if (pid < 0)
			return (error_system(shell, PIPE_FORK));
		else if (pid != 0)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			while ((*command)->next != NULL
					&& (*token)->id < (*command)->next->id)
				*token = (*token)->next;
			handle_pipe(shell, &(*command)->next, token);
			waitpid(pid, &g_signal, 0);
		}
		else
			child_process(fd, shell, *command, *token);
	}
	return (0);
}

void	child_process(int *fd, t_shell *shell, t_command *command,
		t_token *token)
{
//	ft_putstr_fd(token->content, STDERR_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	handle_command(shell, token, command);
	exit(g_signal);
}
