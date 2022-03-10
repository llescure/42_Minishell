#include "../../include/minishell.h"

int		tokenizer(t_double_list *token, t_shell *shell)
{
	t_type	*type;
	int		id;

	set_path(shell);
	id = 0;
	if (token->content != NULL)
	{
		if (check_first_content(token->content, &type, shell, id) < 0)
			return (g_signal);
	}
	if (type == NULL)
	{
		g_signal = -1;
		return (g_signal);
	}
	token = token->next;
	id++;
	while (token != NULL)
	{
		if (check_content(token->content, &type, shell, id) < 0)
			return (g_signal);
		token = token->next;
		id++;
	}
	shell->type = type;
	return (0);
}

int		check_first_content(char *str, t_type **type, t_shell *shell, int id)
{
	if (str[0] == '|' && str[1] == '\0')
		*type = ft_type_new(PIPE, id);
	else if (str[0] == '|' && str[1] == '|')
		*type = ft_type_new(ERROR, id);
	else if (str[0] == '"' && number_occurence_cara_in_str(str, '"') >= 2)
		*type = ft_type_new(D_QUOTE, id);
	else if (str[0] == '\'' && number_occurence_cara_in_str(str, '\'') >= 2)
		*type = ft_type_new(QUOTE, id);
	else if (str[0] == '<' || str[0] == '>')
		check_first_redirection(str, type, id);
	else if (number_occurence_cara_in_str(str, '$') >= 1 || str[0] == '='
			|| (str[0] == '-' && ft_isalnum(str[1]) == 1))
		check_first_special_cara(str, type, id);
	else if (ft_is_only_space(str) == 1)
		*type = ft_type_new(WHITE_SPACE, id);
	else if (ft_isascii(str[0]) == 1)
	{
		if (check_command(str, shell) == 1)
			*type = ft_type_new(COMMAND, id);
		else if (check_command(str, shell) == 0)
			*type = ft_type_new(WORD, id);
		else if (check_command(str, shell) == -1)
			return (g_signal);
	}
	return (0);
}

int		check_content(char *str, t_type **type, t_shell *shell, int id)
{
	if (str[0] == '|' && str[1] == '\0')
		ft_type_add_back(type, ft_type_new(PIPE, id));
	else if (str[0] == '|' && str[1] == '|')
		ft_type_add_back(type, ft_type_new(ERROR, id));
	else if (str[0] == '"' && number_occurence_cara_in_str(str, '"') >= 2)
		ft_type_add_back(type, ft_type_new(D_QUOTE, id));
	else if (str[0] == '\'' && number_occurence_cara_in_str(str, '\'') >= 2)
		ft_type_add_back(type, ft_type_new(QUOTE, id));
	else if (str[0] == '<' || str[0] == '>')
		check_redirection(str, type, id);
	else if (str[0] == '$' || str[0] == '='
			|| (str[0] == '-' && ft_isalnum(str[1]) == 1))
		check_special_cara(str, type, id);
	else if (ft_is_only_space(str) == 1)
		ft_type_add_back(type, ft_type_new(WHITE_SPACE, id));
	else if (ft_isascii(str[0]) == 1)
	{
		if (check_command(str, shell) == 1)
			ft_type_add_back(type, ft_type_new(COMMAND, id));
		else if (check_command(str, shell) == 0)
			ft_type_add_back(type, ft_type_new(WORD, id));
		else if (check_command(str, shell) == -1)
			return (g_signal);
	}
	return (0);
}
