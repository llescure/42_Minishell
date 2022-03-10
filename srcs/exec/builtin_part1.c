/*#include "../../include/minishell.h"

void	ft_echo(t_shell *shell, t_type *type, t_double_list *token)
{
	char	*str;
	char	*temp;
	int	command_option_active;

	type = type->next;
	token = token->next;
	command_option_active = handle_cases_other_than_words(shell, type, token);
	if (command_option_active < 0)
		return ;
	str = ft_strdup("");
	while (type != NULL && token != NULL)
	{
		if (type->content == PIPE)
			return ;
		else if (type->content == WORD || type->content == WHITE_SPACE
			|| type->content == QUOTE || type->content == D_QUOTE
			|| type->content == EXPAND || type->content == COMMAND)
		{
			temp = str;
			str = ft_strjoin(str, shell->token_bis[shell->i]);
			free(temp);
		}
		type = type->next;
		token = token->next;
	}
	ft_putstr_fd(str, shell->fd_outfile);
	if (command_option_active == 0)
		ft_putstr_fd("\n", shell->fd_outfile);
	free(str);
	exit(g_signal);
}

int	handle_cases_other_than_words(t_shell *shell, t_type *type,
		t_double_list *token)
{
	int	command_option_active;

	command_option_active = 0;
	if (token == NULL)
	{
		ft_putstr_fd("\n", shell->fd_outfile);
		return (-1);
	}
	while (type != NULL && (type->content == COMMAND_OPTION
		&& number_occurence_cara_in_str(token->content, 'n')
		== (int)ft_strlen(token->content) - 1)
		|| (ft_strncmp(token->content, " ", ft_strlen(token->content)) == 0))
	{
		if (type->content == COMMAND_OPTION)
			command_option_active = 1;
		token = token->next;
		type = type->next;
	}
	return (command_option_active);
}

void	ft_pwd(t_shell *shell)
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

void	ft_cd(t_shell *shell, t_type *type, t_double_list *token)
{
	int	return_value;

	type = type->next;
	token = token->next;
	while (token != NULL && type != NULL && type->content == WHITE_SPACE)
	{
		type = type->next;
		token = token->next;
	}
	if (token == NULL)
		chdir(shell->absolute_path);
	return_value = chdir(token->content);
	if (return_value == -1)
		error_message(FILES, 1);
}

void	execute_binary(t_shell *shell, t_type *type, t_double_list *token)
{
	char	*temp;
	char	**command;

	if (shell->path != NULL)
	{
		free(shell->path);
		shell->path = NULL;
	}
	set_path(shell);
	command = create_binary(shell, type, token);
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

char	**create_binary(t_shell *shell, t_type *type, t_double_list *token)
{
	char	**command;
	int		i;

	command = malloc(sizeof(char *) * (command_lenght(shell, type, token) + 1));
	if (command == NULL)
		return (NULL);
	i = 0;
	while (token != NULL && (type->content == WHITE_SPACE
		|| type->content == COMMAND_OPTION || type->content == COMMAND
		|| type->content == WORD))
	{
		if (type->content == WHITE_SPACE)
		{
			type = type->next;
			token = token->next;
		}
		if (shell->token_bis[shell->i] == NULL
			|| (type->content != WORD && type->content != COMMAND_OPTION
			&&	type->content != COMMAND))
			break;
		command[i] = ft_strdup(token->content);
		type = type->next;
		token = token->next;
		i++;
	}
	command[i] = NULL;
	return (command);
}

int		command_lenght(t_shell *shell, t_type *type, t_double_list *token)
{
	int	size;

	size = 1;
	while (token != NULL && (type->content == WHITE_SPACE
		|| type->content == COMMAND_OPTION || type->content == COMMAND
		|| type->content == WORD))
	{
		if (type->content == WHITE_SPACE)
		{
			type = type->next;
			token = token->next;
		}
			if (shell->token_bis[index] == NULL)
			break;
		size++;
		type = type->next;
		token = token->next;
	}
	return (size);
}*/
