#include "../../include/minishell.h"

int		tokenizer(t_list *token, t_shell *shell)
{
	t_list	*list;

	if (token->content != NULL)
		check_first_content(token->content, &list);
	if (list == NULL)
	{
		g_signal = -1;
		return (g_signal);
	}
	token = token->next;
	while (token != NULL)
	{
		check_content(token->content, &list);
		token = token->next;
	}
	shell->type = list;
	return (0);
}

void	check_first_content(char *str, t_list **list)
{
	if (str[0] == '|' && str[1] == '\0')
		*list = ft_lstnew("pipe");
	else if (str[0] == '|' && str[1] == '|')
		*list = ft_lstnew("error");
	else if (str[0] == '\'')
		*list = ft_lstnew("single_quote");
	else if (str[0] == '"')
		*list = ft_lstnew("double_quote");
	else if (str[0] == '<' || str[0] == '>')
		check_first_redirection(str, list);
	else if (str[0] == '$' && ft_isalnum(str[1]) == 1)
		*list = ft_lstnew("expand");
	else if (str[0] == '-' && ft_isalnum(str[1]) == 1)
		*list = ft_lstnew("command_option");
	else if (ft_isalnum(str[0]) == 1)
	{
//		if (check_command(str) == 1)
//			*list = ft_lstnew("command");
//		else
			*list = ft_lstnew("word");
	}
}

void	check_content(char *str, t_list **list)
{
	if (str[0] == '|' && str[1] == '\0')
		return (ft_lstadd_back(list, ft_lstnew("pipe")));
	else if (str[0] == '|' && str[1] == '|')
		return (ft_lstadd_back(list, ft_lstnew("error")));
	else if (str[0] == '\'')
		return (ft_lstadd_back(list, ft_lstnew("single_quote")));
	else if (str[0] == '"')
		return (ft_lstadd_back(list, ft_lstnew("double_quote")));
	else if (str[0] == '<' || str[0] == '>')
		return (check_redirection(str, list));
	else if (str[0] == '$' && ft_isalnum(str[1]) == 1)
		return (ft_lstadd_back(list, ft_lstnew("expand")));
	else if (str[0] == '-' && ft_isalnum(str[1]) == 1)
		return (ft_lstadd_back(list, ft_lstnew("command_option")));
	else if (ft_isalnum(str[0]) == 1)
	{
	//	if (check_command(str) == 1)
	//		return (ft_lstadd_back(list, ft_lstnew("command")));
	//	else
			return (ft_lstadd_back(list, ft_lstnew("word")));
	}
}

void	check_first_redirection(char *str, t_list **list)
{
	if (str[0] == '<' && str[1] == '\0')
		*list = ft_lstnew("redir_left");
	else if (str[0] == '<' && str[1] == '<' && str[2] == '\0')
		*list = ft_lstnew("heredoc");
	else if (str[0] == '<' && str[1] == '<' && str[2] == '<')
		*list = ft_lstnew("error");
	else if (str[0] == '>' && str[1] == '\0')
		*list = ft_lstnew("redir_right");
	else if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
		*list = ft_lstnew("d_redir_right");
	else if (str[0] == '>' && str[1] == '>' && str[2] == '>')
		*list = ft_lstnew("error");
}

void	check_redirection(char *str, t_list **list)
{
	if (str[0] == '<' && str[1] == '\0')
		return (ft_lstadd_back(list, ft_lstnew("redir_left")));
	else if (str[0] == '<' && str[1] == '<' && str[2] == '\0')
		return (ft_lstadd_back(list, ft_lstnew("heredoc")));
	else if (str[0] == '<' && str[1] == '<' && str[2] == '<')
		return (ft_lstadd_back(list, ft_lstnew("error")));
	else if (str[0] == '>' && str[1] == '\0')
		return (ft_lstadd_back(list, ft_lstnew("redir_right")));
	else if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
		return (ft_lstadd_back(list, ft_lstnew("d_redir_right")));
	else if (str[0] == '>' && str[1] == '>' && str[2] == '>')
		return (ft_lstadd_back(list, ft_lstnew("error")));
}
