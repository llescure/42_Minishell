#include "../../include/minishell.h"

int		tokenizer(t_double_list *token, t_shell *shell)
{
	t_double_list	*list;

	set_path(shell);
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
		*list = ft_double_lstnew((int)PIPE);
	else if (str[0] == '|' && str[1] == '|')
		*list = ft_double_lstnew((int)ERROR);
	else if (str[0] == '"' && number_occurence_cara_in_str(str, '"') >= 2)
		*list = ft_double_lstnew((int)D_QUOTE);
	else if (str[0] == '\'' && number_occurence_cara_in_str(str, '\'') >= 2)
		*list = ft_double_lstnew((int)QUOTE);
	else if (str[0] == '<' || str[0] == '>')
		check_first_redirection(str, list);
	else if (number_occurence_cara_in_str(str, '$') >= 1 || str[0] == '='
			|| (str[0] == '-' && ft_isalnum(str[1]) == 1))
		check_first_special_cara(str, list);
	else if (ft_is_only_space(str) == 1)
		*list = ft_double_lstnew((int)WHITE_SPACE);
	else if (ft_isascii(str[0]) == 1)
	{
		if (check_command(str, shell) == 1)
			*list = ft_double_lstnew((int)COMMAND);
		else if (check_command(str, shell) == 0)
			*list = ft_double_lstnew((int)WORD);
		else if (check_command(str, shell) == -1)
			return (g_signal);
	}
	return (0);
}

int		check_content(char *str, t_double_list **list, t_shell *shell)
{
	if (str[0] == '|' && str[1] == '\0')
		ft_double_lstadd_back(list, ft_double_lstnew((int)PIPE));
	else if (str[0] == '|' && str[1] == '|')
		ft_double_lstadd_back(list, ft_double_lstnew((int)ERROR));
	else if (str[0] == '"' && number_occurence_cara_in_str(str, '"') >= 2)
		ft_double_lstadd_back(list, ft_double_lstnew((int)D_QUOTE));
	else if (str[0] == '\'' && number_occurence_cara_in_str(str, '\'') >= 2)
		ft_double_lstadd_back(list, ft_double_lstnew((int)QUOTE));
	else if (str[0] == '<' || str[0] == '>')
		check_redirection(str, list);
	else if (str[0] == '$' || str[0] == '='
			|| (str[0] == '-' && ft_isalnum(str[1]) == 1))
		check_special_cara(str, list);
	else if (ft_is_only_space(str) == 1)
		ft_double_lstadd_back(list, ft_double_lstnew((int)WHITE_SPACE));
	else if (ft_isascii(str[0]) == 1)
	{
		if (check_command(str, shell) == 1)
			ft_double_lstadd_back(list, ft_double_lstnew((int)COMMAND));
		else if (check_command(str, shell) == 0)
			ft_double_lstadd_back(list, ft_double_lstnew((int)WORD));
		else if (check_command(str, shell) == -1)
			return (g_signal);
	}
	return (0);
}
