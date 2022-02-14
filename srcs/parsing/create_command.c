#include "../../include/minishell.h"

char	*find_correct_path(char **path, char *cmd)
{
	int		i;
	char	*temp;
	char	*command;
	i = 0;
	temp = create_command_path(cmd);
	if (temp == NULL)
		return (temp);
	while (path != NULL && path[i] != NULL)
	{
		command = ft_strjoin(path[i], temp);
		if (command == NULL)
		{
			g_signal = -1;
			free(temp);
			return (NULL);
		}
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
		g_signal = -1;
	return (rslt);
}
