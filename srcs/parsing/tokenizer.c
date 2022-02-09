#include "../../include/minishell.h"

int		tokenizer(t_list *token, t_shell *shell)
{
	t_double_list	*list;

	if (token->content != NULL)
	{
		if (check_first_content(token->content, &list, shell) < 0)
			return (g_signal);
	}
	if (list == NULL)
	{
		g_signal = -1;
		return (g_signal);
	}
	token = token->next;
	while (token != NULL)
	{
		if (check_content(token->content, &list, shell) < 0)
			return (g_signal);
		token = token->next;
	}
	shell->type = list;
	return (0);
}

int		check_first_content(char *str, t_double_list **list, t_shell *shell)
{
	if (str[0] == '|' && str[1] == '\0')
		*list = ft_double_lstnew((char *)"pipe");
	else if (str[0] == '|' && str[1] == '|')
		*list = ft_double_lstnew((char *)"error");
	else if (str[0] == '\'')
		*list = ft_double_lstnew((char *)"single_quote");
	else if (str[0] == '"')
		*list = ft_double_lstnew((char *)"double_quote");
	else if (str[0] == '<' || str[0] == '>')
		check_first_redirection(str, list);
	else if (str[0] == '$')
		*list = ft_double_lstnew((char *)"expand");
	else if (str[0] == '=')
		*list = ft_double_lstnew((char *)"equal");
	else if (str[0] == '-' && ft_isalnum(str[1]) == 1)
		*list = ft_double_lstnew((char *)"command_option");
	else if (ft_isascii(str[0]) == 1)
	{
		if (check_command(str, shell) == 1)
			*list = ft_double_lstnew((char *)"command");
		else if (check_command(str, shell) == 0)
			*list = ft_double_lstnew((char *)"word");
		else if (check_command(str, shell) == -1)
			return (g_signal);
	}
	return (0);
}

int		check_content(char *str, t_double_list **list, t_shell *shell)
{
	if (str[0] == '|' && str[1] == '\0')
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"pipe"));
	else if (str[0] == '|' && str[1] == '|')
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"error"));
	else if (str[0] == '\'')
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"single_quote"));
	else if (str[0] == '"')
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"double_quote"));
	else if (str[0] == '<' || str[0] == '>')
		check_redirection(str, list);
	else if (str[0] == '$')
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"expand"));
	else if (str[0] == '=')
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"equal"));
	else if (str[0] == '-' && ft_isalnum(str[1]) == 1)
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"command_option"));
	else if (ft_isascii(str[0]) == 1)
	{
		if (check_command(str, shell) == 1)
			ft_double_lstadd_back(list, ft_double_lstnew((char *)"command"));
		else if (check_command(str, shell) == 0)
			ft_double_lstadd_back(list, ft_double_lstnew((char *)"word"));
		else if (check_command(str, shell) == -1)
			return (g_signal);
	}
	return (0);
}

int		check_command(char *str, t_shell *shell)
{
	char	*temp;
	if (ft_strncmp(str, "exit", ft_strlen("exit")) == 0
			|| ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0
			|| ft_strncmp(str, "echo", ft_strlen("echo")) == 0
			|| ft_strncmp(str, "cd", ft_strlen("cd")) == 0
			|| ft_strncmp(str, "export", ft_strlen("export")) == 0
			|| ft_strncmp(str, "unset", ft_strlen("unset")) == 0
			|| ft_strncmp(str, "env", ft_strlen("env")) == 0)
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

void	check_first_redirection(char *str, t_double_list **list)
{
	if (str[0] == '<' && str[1] == '\0')
		*list = ft_double_lstnew((char *)"redir_left");
	else if (str[0] == '<' && str[1] == '<' && str[2] == '\0')
		*list = ft_double_lstnew((char *)"heredoc");
	else if (str[0] == '<' && str[1] == '<' && str[2] == '<')
		*list = ft_double_lstnew((char *)"error");
	else if (str[0] == '>' && str[1] == '\0')
		*list = ft_double_lstnew((char *)"redir_right");
	else if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
		*list = ft_double_lstnew((char *)"d_redir_right");
	else if (str[0] == '>' && str[1] == '>' && str[2] == '>')
		*list = ft_double_lstnew((char *)"error");
}

void	check_redirection(char *str, t_double_list **list)
{
	if (str[0] == '<' && str[1] == '\0')
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"redir_left"));
	else if (str[0] == '<' && str[1] == '<' && str[2] == '\0')
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"heredoc"));
	else if (str[0] == '<' && str[1] == '<' && str[2] == '<')
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"error"));
	else if (str[0] == '>' && str[1] == '\0')
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"redir_right"));
	else if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"d_redir_right"));
	else if (str[0] == '>' && str[1] == '>' && str[2] == '>')
		ft_double_lstadd_back(list, ft_double_lstnew((char *)"error"));
}
