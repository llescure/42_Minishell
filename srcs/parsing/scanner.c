#include "../../include/minishell.h"

/*
 ** This function skips white_space. If a single quote or double quote is
 **	encountered this function makes sure that an other single or double quote
 ** is found. Otherwise it skips the caracter.
 */

int	ft_beginning_lexeme(char *str, int pos, int *found_quote)
{
	int	i;

	i = pos;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (ft_iscara(str[i], '\'') == 1)
	{
		if (look_for_quote(str, i, '\'') == i + 1)
			return (look_for_quote(str, i, '\''));
		else
			*found_quote = 1;
	}
	else if (ft_iscara(str[i], '"') == 1)
	{
		if (look_for_quote(str, i, '"') == i + 1)
			return (look_for_quote(str, i, '"'));
		else
			*found_quote = 1;
	}
	return (i);
}

int	ft_end_lexeme(char *str, int pos, int found_quote)
{
	int	i;

	i = pos;
	if (found_quote == 1)
		return (look_for_quote(str, i, str[i]));
	while (ft_isspace(str[i]) == 0 && str[i] != '\0')
	{
		if (str[i] == '|')
			return (delimit_separator(str, i, str[i], pos));
		else if (ft_isredirections(str[i]) == 1)
			return (delimit_separator(str, i, str[i], pos));
		else if (str[i] == '=')
			return (delimit_separator(str, i, str[i], pos));
		else if (str[i] == '$')
			return (delimit_expand(str, i));
		else if (str[i] == '\'' || str[i] == '"')
			return (i);
		i++;
	}
	return (i);
}

char	*find_lexeme(char *user_input, int starting_point, int *end)
{
	char	*temp;
	int	beginning;
	int	found_quote;

	found_quote = 0;
	beginning = ft_beginning_lexeme(user_input, starting_point, &found_quote);
	*end = ft_end_lexeme(user_input, beginning, found_quote);
	temp = ft_cut_str(user_input, beginning, *end);
	return (temp);
}

/*
 ** Scan the user_input to find lexeme delimited by whitespace, pipe, quote,
 ** redirections and put it into a linked list in the structure
 */

int		scanner(char *user_input, t_shell *shell)
{
	t_list	*list;
	int		end;
	char	*temp;

	temp = find_lexeme(user_input, 0, &end);
	if (temp != NULL)
		list = ft_lstnew(temp);
	if (list == NULL)
	{
		g_signal = -1;
		return (g_signal);
	}
	while (end < (int)ft_strlen(user_input))
	{
		temp = find_lexeme(user_input, end, &end);
		if (temp == NULL && g_signal == -1)
			return (g_signal);
		else if (temp == NULL)
			end++;
		if (temp != NULL)
			ft_lstadd_back(&list, ft_lstnew(temp));
	}
	shell->token = list;
	return (0);
}
