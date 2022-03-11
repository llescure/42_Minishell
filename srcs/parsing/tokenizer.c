#include "../../include/minishell.h"

int		tokenizer(t_token *token, t_shell *shell)
{
	set_path(shell);
	while (token != NULL)
	{
		if (check_content(token->content, &token, shell) < 0)
			return (g_signal);
		token = token->next;
	}
	return (0);
}

int		check_content(char *str, t_token **token, t_shell *shell)
{
	if (str[0] == '|' && str[1] == '\0')
		(*token)->type = PIPE;
	else if (str[0] == '|' && str[1] == '|')
		(*token)->type = ERROR;
	else if (str[0] == '"' && number_occurence_cara_in_str(str, '"') >= 2)
		(*token)->type = D_QUOTE;
	else if (str[0] == '\'' && number_occurence_cara_in_str(str, '\'') >= 2)
		(*token)->type = QUOTE;
	else if (str[0] == '<' || str[0] == '>')
		check_redirection(str, token);
	else if (str[0] == '$' || str[0] == '='
			|| (str[0] == '-' && ft_isalnum(str[1]) == 1))
		check_special_cara(str, token);
	else if (ft_is_only_space(str) == 1)
		(*token)->type = WHITE_SPACE;
	else if (ft_isascii(str[0]) == 1)
	{
		if (check_command(str, shell) == 1)
			(*token)->type = COMMAND;
		else if (check_command(str, shell) == 0)
			(*token)->type = WORD;
		else if (check_command(str, shell) == 0)
			return (g_signal);
	}
	return (0);
}

void	check_special_cara(char *str, t_token **token)
{
	if (number_occurence_cara_in_str(str, '$') >= 1)
		(*token)->type = EXPAND;
	else if (str[0] == '=')
		(*token)->type = EQUAL;
	else if (str[0] == '-' && ft_isalnum(str[1]) == 1)
		(*token)->type = COMMAND_OPTION;
}

int		check_command(char *str, t_shell *shell)
{
	char	*temp;
	if ((ft_strncmp(str, "exit", ft_strlen("exit")) == 0
			&& ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		|| (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0
			&& ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		|| (ft_strncmp(str, "echo", ft_strlen("echo")) == 0
			&& ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		|| (ft_strncmp(str, "cd", ft_strlen("cd")) == 0
			&& ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		|| (ft_strncmp(str, "export", ft_strlen("export")) == 0
			&& ft_strncmp(str, "export", ft_strlen(str)) == 0)
		|| (ft_strncmp(str, "unset", ft_strlen("unset")) == 0
			&& ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		|| (ft_strncmp(str, "./", ft_strlen("./")) == 0)
		|| (ft_strncmp(str, "env", ft_strlen("env")) == 0
			&& ft_strncmp(str, "env", ft_strlen(str)) == 0))
		return (1);
	temp = find_correct_path(shell->path, str);
	if (temp != NULL)
	{
		free(temp);
		return (1);
	}
	else if (temp == NULL && g_signal == -1)
	{
		free(temp);
		return (g_signal);
	}
	free(temp);
	return (0);
}

void	check_redirection(char *str, t_token **token)
{
	int	i;
	t_type	type;

	i = 1;
	if (str[0] == '<')
		type = REDIR_LEFT;
	else if (str[0] == '>')
		type = REDIR_RIGHT;
	if (str[0] == '<' && str[1] == '<')
		type = HEREDOC;
	if (str[0] == '>' && str[1] == '>')
		type = D_REDIR_RIGHT;
	if	((str[0] == '<' && str[1] == '<' && str[2] == '<')
	 	|| (str[0] == '>' && str[1] == '>' && str[2] == '>')
	 	|| (str[0] == '>' && str[1] == '<')
	 	|| (str[0] == '<' && str[1] == '>')
	 	|| (str[0] == '<' && str[1] == '<' && str[2] == '>')
	 	|| (str[0] == '>' && str[1] == '>' && str[2] == '<'))
		type = ERROR;
	while (str[i] != '\0' && ft_isalnum(str[i]) == 0)
		i++;
	if (str[i] == '\0')
		(*token)->type = ERROR;
	else
		(*token)->type = type;
}
