#include "../../include/minishell.h"

int		parsing(char *user_input, t_shell *shell)
{
//	int pid;
//	int status;

//	status = 0;
	if (user_input[0] == '\0')
		return (0);
	if (scanner(user_input, shell) < 0)
	{
		error_message("malloc");
		return (g_signal);
	}
	if (tokenizer(shell->token, shell) < 0)
	{
		error_message("malloc");
		return (g_signal);
	}
	ft_print_list(shell->token);
	ft_putstr_fd("\n", 1);
	ft_double_print_list(shell->type);
	if (look_for_error_in_type(shell->type) == 1)
	{
		error_message("syntax");
		return (g_signal);
	}
	look_for_grammar_error(shell->token, shell->type);
	/*
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
		g_signal += 128;*/
	return (0);
}

int		look_for_error_in_type(t_double_list *list)
{
	while (list != NULL)
	{
		if (ft_strncmp(list->content, "error", ft_strlen("error")) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}

void	look_for_grammar_error(t_list *list, t_double_list *type)
{
	while (list != NULL && type != NULL)
	{
		if (ft_strncmp(type->content, "
		list = list->next;
		type = type->next;
	}
}

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
