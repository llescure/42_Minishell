/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 07:59:45 by llescure          #+#    #+#             */
/*   Updated: 2022/04/07 14:34:33 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	find_type_command(char *str, t_command **command)
{
	if (double_ft_strncmp(str, "exit") == 1)
		(*command)->command_type = EXIT;
	else if (double_ft_strncmp(str, "pwd") == 1)
		(*command)->command_type = PWD;
	else if (double_ft_strncmp(str, "echo") == 1)
		(*command)->command_type = ECHO_CMD;
	else if (double_ft_strncmp(str, "cd") == 1)
		(*command)->command_type = CD;
	else if (double_ft_strncmp(str, "export") == 1)
		(*command)->command_type = EXPORT;
	else if (double_ft_strncmp(str, "unset") == 1)
		(*command)->command_type = UNSET;
	else if (double_ft_strncmp(str, "env") == 1)
		(*command)->command_type = ENV;
	else if (ft_strncmp(str, "./", ft_strlen("./")) == 0)
		(*command)->command_type = EXECUTABLE;
	else
		(*command)->command_type = BINARY;
}
