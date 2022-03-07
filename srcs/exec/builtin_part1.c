#include "../../include/minishell.h"

/*void	ft_echo(t_shell *shell)
{
	char	*str;
	char	*temp;
	char	*type;
	int	command_option_active;

	shell->i++;
	if (handle_cases_other_than_words(shell, &command_option_active) != 0)
		return ;
	str = ft_strdup("");
	while (shell->type_bis[shell->i] != NULL)
	{
		type = shell->type_bis[shell->i];
		if (ft_strncmp(type, "pipe", ft_strlen("pipe")) == 0)
			return ;
		else if (ft_strncmp(type, "word", ft_strlen("word")) == 0
			|| ft_strncmp(type, "white_space", ft_strlen("white_space")) == 0
			|| ft_strncmp(type, "single_quote", ft_strlen("single_quote")) == 0
			|| ft_strncmp(type, "double_quote", ft_strlen("double_quote")) == 0
			|| ft_strncmp(type, "expand", ft_strlen("expand")) == 0
			|| ft_strncmp(type, "command", ft_strlen("command")) == 0)
		{
			temp = str;
			str = ft_strjoin(str, shell->token_bis[shell->i]);
			free(temp);
		}
		shell->i++;
	}
	ft_putstr_fd(str, shell->fd_outfile);
	if (command_option_active == 0)
		ft_putstr_fd("\n", shell->fd_outfile);
	free(str);
	exit(g_signal);
}

int	handle_cases_other_than_words(t_shell *shell,
		int *command_option_active)
{
	*command_option_active = 0;
	if (shell->token_bis[shell->i] == NULL)
	{
		ft_putstr_fd("\n", shell->fd_outfile);
		return (-1);
	}
	shell->i++;
	while (shell->type_bis[shell->i] != NULL &&
			((ft_strncmp(shell->type_bis[shell->i], "command_option",
						 ft_strlen("command_option")) == 0
			  && number_occurence_cara_in_str(shell->token_bis[shell->i], 'n')
			  == (int)ft_strlen(shell->token_bis[shell->i]) - 1)
			 || (ft_strncmp(shell->token_bis[shell->i], " ",
					 ft_strlen(shell->token_bis[shell->i])) == 0)))
	{
		if (ft_strncmp(shell->type_bis[shell->i], "command_option",
					ft_strlen("command_option")) == 0)
			*command_option_active = 1;
		shell->i++;
	}
	return (0);
}

void ft_pwd(t_shell *shell)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (shell->pwd != NULL)
			free(shell->pwd);
		shell->pwd = ft_strdup(cwd);
		ft_putstr_fd(shell->pwd, shell->fd_outfile);
		ft_putstr_fd("\n", shell->fd_outfile);
	}
	exit(g_signal);
}

void	ft_cd(t_shell *shell)
{
	int	return_value;

	shell->i++;
	while (shell->token_bis[shell->i] != NULL &&
			ft_strncmp(shell->type_bis[shell->i], "white_space",
				ft_strlen("white_space")) == 0)
		shell->i++;
	if (shell->token_bis[shell->i] == NULL)
		chdir(shell->absolute_path);
	return_value = chdir(shell->token_bis[shell->i]);
	if (return_value == -1)
		error_message(FILES, shell->fd_outfile);
}

void	execute_binary(t_shell *shell)
{
	char	*temp;
	char	**command;

	if (shell->path != NULL)
	{
		free(shell->path);
		shell->path = NULL;
	}
	set_path(shell);
	command = create_binary(shell);
	if (command == NULL)
	{
		error_message(MALLOC, 0);
		exit(g_signal);
	}
	if (shell->path != NULL)
	{
		temp = command[0];
		command[0] = find_correct_path(shell->path, command[0]);
		free(temp);
	}
	if (execve(command[0], command, shell->env->env) < 0)
	{
		error_message(COMMAND_ERROR, 1);
		free_tab(command);
		exit(g_signal);
	}
	free_tab(command);
}

char	**create_binary(t_shell *shell)
{
	char	**command;
	int		i;

	command = malloc(sizeof(char *) * (command_lenght(shell, shell->i) + 1));
	if (command == NULL)
		return (NULL);
	i = 0;
	while (shell->token_bis[shell->i] != NULL
		&& (ft_strncmp(shell->type_bis[shell->i], "white_space",
				ft_strlen("white_space")) == 0
		|| ft_strncmp(shell->type_bis[shell->i], "command_option",
				ft_strlen("command_option")) == 0
		|| ft_strncmp(shell->type_bis[shell->i], "command",
				ft_strlen("command")) == 0
		|| ft_strncmp(shell->type_bis[shell->i], "word",
				ft_strlen("word")) == 0))
	{
		if (ft_strncmp(shell->type_bis[shell->i], "white_space",
				ft_strlen("white_space")) == 0)
			shell->i++;
		if (shell->token_bis[shell->i] == NULL
			|| (ft_strncmp(shell->type_bis[shell->i], "word",
				ft_strlen("word")) != 0
			&&	ft_strncmp(shell->type_bis[shell->i], "command_option",
				ft_strlen("command_option")) != 0
			&&	ft_strncmp(shell->type_bis[shell->i], "command",
				ft_strlen("command")) != 0))
			break;
		command[i] = ft_strdup(shell->token_bis[shell->i]);
		shell->i++;
		i++;
	}
	command[i] = NULL;
	return (command);
}

int		command_lenght(t_shell *shell, int index)
{
	int	size;

	size = 1;
	while (shell->token_bis[index] != NULL
		&& (ft_strncmp(shell->type_bis[index], "white_space",
				ft_strlen("white_space")) == 0
		|| ft_strncmp(shell->type_bis[index], "command_option",
				ft_strlen("command_option")) == 0
		|| ft_strncmp(shell->type_bis[index], "command",
				ft_strlen("command")) == 0
		|| ft_strncmp(shell->type_bis[index], "word",
				ft_strlen("word")) == 0))
	{
		if (ft_strncmp(shell->type_bis[index], "white_space",
				ft_strlen("white_space")) == 0)
			index++;
		if (shell->token_bis[index] == NULL)
			break;
		size++;
		index++;
	}
	return (size);
}*/
