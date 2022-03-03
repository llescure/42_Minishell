#include "../../include/minishell.h"

void	check_first_special_cara(char *str, t_double_token **token)
{
	if (number_occurence_cara_in_str(str, '$') >= 1)
		*token = ft_double_lstnew((int)EXPAND);
	else if (str[0] == '=')
		*token = ft_double_lstnew((int)EQUAL);
	else if (str[0] == '-' && ft_isalnum(str[1]) == 1)
		*token = ft_double_lstnew((int)COMMAND_OPTION);
}

void	check_special_cara(char *str, t_double_token **token)
{
	if (number_occurence_cara_in_str(str, '$') >= 1)
		ft_double_lstadd_back(token, ft_double_lstnew((int)EXPAND));
	else if (str[0] == '=')
		ft_double_lstadd_back(token, ft_double_lstnew((int)EQUAL));
	else if (str[0] == '-' && ft_isalnum(str[1]) == 1)
		ft_double_lstadd_back(token, ft_double_lstnew((int)COMMAND_OPTION));
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

void	check_first_redirection(char *str, t_double_token **token)
{
	if (str[0] == '<' && str[1] == '\0')
		*token = ft_double_lstnew((int)REDIR_LEFT);
	else if (str[0] == '<' && str[1] == '<' && str[2] == '\0')
		*token = ft_double_lstnew((int)HEREDOC);
	else if (str[0] == '<' && str[1] == '<' && str[2] == '<')
		*token = ft_double_lstnew((int)ERROR);
	else if (str[0] == '>' && str[1] == '\0')
		*token = ft_double_lstnew((int)REDIR_RIGHT);
	else if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
		*token = ft_double_lstnew((int)D_REDIR_RIGHT);
	else if (str[0] == '>' && str[1] == '>' && str[2] == '>')
		*token = ft_double_lstnew((int)ERROR);
}

void	check_redirection(char *str, t_double_token **token)
{
	if (str[0] == '<' && str[1] == '\0')
		ft_double_lstadd_back(token, ft_double_lstnew((int)REDIR_LEFT));
	else if (str[0] == '<' && str[1] == '<' && str[2] == '\0')
		ft_double_lstadd_back(token, ft_double_lstnew((int)HEREDOC));
	else if (str[0] == '<' && str[1] == '<' && str[2] == '<')
		ft_double_lstadd_back(token, ft_double_lstnew((int)ERROR));
	else if (str[0] == '>' && str[1] == '\0')
		ft_double_lstadd_back(token, ft_double_lstnew((int)REDIR_RIGHT));
	else if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
		ft_double_lstadd_back(token, ft_double_lstnew((int)D_REDIR_RIGHT));
	else if (str[0] == '>' && str[1] == '>' && str[2] == '>')
		ft_double_lstadd_back(token, ft_double_lstnew((int)ERROR));
}
