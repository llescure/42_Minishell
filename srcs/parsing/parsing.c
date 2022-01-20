#include "../../include/minishell.h"

int		parsing(char *user_input, t_shell *shell)
{
	int pid;
	int status;

	status = 0;
	shell->cmd = ft_split(user_input, ' ');
	free(shell->cmd[0]);
	shell->cmd[0] = find_correct_path(shell->path, user_input);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		if (ft_strncmp(user_input, "cat", ft_strlen("cat")) == 0)
		{
			if (execve(shell->cmd[0], shell->cmd, shell->env->env) < -1)
				return (-1);
		}
	}
	else
	{
		signal(SIGINT, handle_exec_signals);
		signal(SIGQUIT, handle_exec_signals);
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, handle_signals);
	}
	g_signal = status;
	if (g_signal == 2)
		g_signal += 128;
	return (0);
}

char	*find_correct_path(char **path, char *cmd)
{
	int		i;
	char	*temp;
	char	*command;

	i = 0;
	temp = create_command_path(cmd);
	while (path != NULL && path[i] != NULL)
	{
		command = ft_strjoin(path[i], temp);
		if (command == NULL)
			exit(0);
		if (access(command, F_OK) != -1)
		{
			free(temp);
			return (command);
		}
		free(command);
		i++;
	}
	free(temp);
	return (NULL);
}

char	*create_command_path(char *cmd)
{
	char	*rslt;

	rslt = ft_strjoin("/", cmd);
	if (rslt == NULL)
	{
		perror("Error while joining two strings");
		exit(EXIT_FAILURE);
	}
	return (rslt);
}
