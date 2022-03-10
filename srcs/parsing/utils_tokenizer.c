#include "../../include/minishell.h"

void	check_first_special_cara(char *str, t_type **type, int id)
{
	if (number_occurence_cara_in_str(str, '$') >= 1)
		*type = ft_type_new(EXPAND, id);
	else if (str[0] == '=')
		*type = ft_type_new(EQUAL, id);
	else if (str[0] == '-' && ft_isalnum(str[1]) == 1)
		*type = ft_type_new(COMMAND_OPTION, id);
}

void	check_special_cara(char *str, t_type **type, int id)
{
	if (number_occurence_cara_in_str(str, '$') >= 1)
		ft_type_add_back(type, ft_type_new(EXPAND, id));
	else if (str[0] == '=')
		ft_type_add_back(type, ft_type_new(EQUAL, id));
	else if (str[0] == '-' && ft_isalnum(str[1]) == 1)
		ft_type_add_back(type, ft_type_new(COMMAND_OPTION, id));
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

void	check_first_redirection(char *str, t_type **type, int id)
{
	int	i;
	t_category	category;

	i = 1;
	if (str[0] == '<')
		category = REDIR_LEFT;
	else if (str[0] == '>')
		category = REDIR_RIGHT;
	if (str[0] == '<' && str[1] == '<')
		category = HEREDOC;
	if (str[0] == '>' && str[1] == '>')
		category = D_REDIR_RIGHT;
	if	((str[0] == '<' && str[1] == '<' && str[2] == '<')
	 	|| (str[0] == '>' && str[1] == '>' && str[2] == '>')
	 	|| (str[0] == '>' && str[1] == '<')
	 	|| (str[0] == '<' && str[1] == '>')
	 	|| (str[0] == '<' && str[1] == '<' && str[2] == '>')
	 	|| (str[0] == '>' && str[1] == '>' && str[2] == '<'))
		category = ERROR;
	while (str[i] != '\0' && ft_isalnum(str[i]) == 0)
		i++;
	if (str[i] == '\0')
		*type = ft_type_new(ERROR, id);
	else
		*type = ft_type_new(category, id);
}

void	check_redirection(char *str, t_type **type, int id)
{
	int	i;
	t_category	category;

	i = 1;
	if (str[0] == '<')
		category = REDIR_LEFT;
	else if (str[0] == '>')
		category = REDIR_RIGHT;
	if (str[0] == '<' && str[1] == '<')
		category = HEREDOC;
	if (str[0] == '>' && str[1] == '>')
		category = D_REDIR_RIGHT;
	if	((str[0] == '<' && str[1] == '<' && str[2] == '<')
	 	|| (str[0] == '>' && str[1] == '>' && str[2] == '>')
	 	|| (str[0] == '>' && str[1] == '<')
	 	|| (str[0] == '<' && str[1] == '>')
	 	|| (str[0] == '<' && str[1] == '<' && str[2] == '>')
	 	|| (str[0] == '>' && str[1] == '>' && str[2] == '<'))
		category = ERROR;
	while (str[i] != '\0' && ft_isalnum(str[i]) == 0)
		i++;
	if (str[i] == '\0')
		ft_type_add_back(type, ft_type_new(ERROR, id));
	else
		ft_type_add_back(type, ft_type_new(category, id));
}
