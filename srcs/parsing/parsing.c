#include "../../include/minishell.h"

int		parsing(char *user_input, t_shell *shell)
{
	printf("path %s", shell->path[2]);
	(void)user_input;
//	shell->cmd[0] = find_correct_path(shell->path, user_input);
	/*if (ft_strncmp(user_input, "cat", ft_strlen("cat")) == 0)
	{
		if (execve(shell->cmd[0], shell->cmd, shell->env->env) < -1)
			return (-1);
	}*/
	return (0);
}

char	*find_correct_path(char **path, char *cmd)
{
	int		i;
	char	*temp;
	char	*temp2;
	char	*command;

	i = 0;
	temp = create_command_path(cmd);
	while (path != NULL && path[i] != NULL)
	{
		command = ft_strjoin(path[i], temp);
		if (command == NULL)
			exit(EXIT_FAILURE);
		if (access(command, F_OK) != -1)
		{
			temp2 = cmd;
			free(temp2);
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
