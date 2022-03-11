#include "../../include/minishell.h"

void	ft_echo(t_shell *shell, t_token **token)
{
	char	*str;
	char	*temp;
	int	command_option_active;

	*token = (*token)->next;
	command_option_active = handle_cases_other_than_words(shell, *token);
	if (command_option_active < 0)
		return ;
	while (*token != NULL && ((*token)->type == WHITE_SPACE
		|| (command_option_active == 1	&& (*token)->type == COMMAND_OPTION)))
		*token = (*token)->next;
	str = ft_strdup("");
	while (*token != NULL)
	{
		if ((*token)->type == PIPE)
			return ;
		else if ((*token)->type == WORD || (*token)->type == WHITE_SPACE
			|| (*token)->type == QUOTE || (*token)->type == D_QUOTE
			|| (*token)->type == EXPAND || (*token)->type == COMMAND
			|| ((*token)->type == COMMAND_OPTION && command_option_active == 0))
		{
			temp = str;
			str = ft_strjoin(str, (*token)->content);
			free(temp);
		}
		*token = (*token)->next;
	}
	ft_putstr_fd(str, shell->fd_outfile);
	if (command_option_active == 0)
		ft_putstr_fd("\n", shell->fd_outfile);
	free(str);
}

int	handle_cases_other_than_words(t_shell *shell, t_token *token)
{
	int	command_option_active;

	command_option_active = 0;
	if (token == NULL)
	{
		ft_putstr_fd("\n", shell->fd_outfile);
		return (-1);
	}
	while (token != NULL && ((token->type == COMMAND_OPTION
		&& number_occurence_cara_in_str(token->content, 'n')
		== (int)ft_strlen(token->content) - 1) || (token->type == WHITE_SPACE)))
	{
		if (token->type == COMMAND_OPTION)
			command_option_active = 1;
		token = token->next;
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

void	ft_cd(t_shell *shell, t_token **token)
{
	int	return_value;

	*token = (*token)->next;
	while (*token != NULL && (*token)->type == WHITE_SPACE)
		*token = (*token)->next;
	if (*token == NULL)
	{
		chdir(shell->absolute_path);
		return;
	}
	return_value = chdir((*token)->content);
	if (return_value == -1)
		error_message(FILES, 1);
}

void	execute_binary(t_shell *shell, t_token *token)
{
	char	*temp;
	char	**command;

	if (shell->path != NULL)
	{
		free(shell->path);
		shell->path = NULL;
	}
	set_path(shell);
	command = create_binary(token);
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

char	**create_binary(t_token *token)
{
	char	**command;
	int		i;

	command = malloc(sizeof(char *) * (command_lenght(token) + 1));
	if (command == NULL)
		return (NULL);
	i = 0;
	while (token != NULL && (token->type == WHITE_SPACE
		|| token->type == COMMAND_OPTION || token->type == COMMAND
		|| token->type == WORD))
	{
		if (token->type == WHITE_SPACE)
			token = token->next;
		if (token == NULL
			|| (token->type != WORD && token->type != COMMAND_OPTION
			&&	token->type != COMMAND))
			break;
		command[i] = ft_strdup(token->content);
		token = token->next;
		i++;
	}
	command[i] = NULL;
	return (command);
}

int		command_lenght(t_token *token)
{
	int	size;

	size = 1;
	while (token != NULL && (token->type == WHITE_SPACE
		|| token->type == COMMAND_OPTION || token->type == COMMAND
		|| token->type == WORD))
	{
		if (token->type == WHITE_SPACE)
			token = token->next;
		if (token == NULL)
			break;
		size++;
		token = token->next;
	}
	return (size);
}

void	execute_executable(t_shell *shell, t_token *token)
{
	char	**command;

	command = create_binary(token);
	if (command == NULL)
	{
		error_message(MALLOC, 0);
		exit(g_signal);
	}
	if (execve(command[0], command, shell->env->env) < 0)
	{
		error_message(COMMAND_ERROR, 1);
		free_tab(command);
		exit(g_signal);
	}
	free_tab(command);
}
