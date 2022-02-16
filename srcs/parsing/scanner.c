#include "../../include/minishell.h"

/*
 ** This function skips white_space. If a single quote or double quote is
 **	encountered this function makes sure that an other single or double quote
 ** is found. Otherwise it skips the caracter.
 */

int	ft_beginning_lexeme(char *str, int pos, int quote_indication)
{
	int	i;

	i = pos;
	if (ft_iscara(str[i], '\'') == 1 && quote_indication == 0)
	{
		if (look_for_quote(str, i, '\'', pos) == pos + 1)
			return (look_for_quote(str, i, '\'', pos));
	}
	else if (ft_iscara(str[i], '"') == 1 && quote_indication == 0)
	{
		if (look_for_quote(str, i, '"', pos) == pos + 1)
			return (look_for_quote(str, i, '"', pos));
	}
	return (i);
}

int	ft_end_lexeme(char *str, int pos, int quote_indication)
{
	int	i;

	i = pos;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			return (delimit_separator(str, i, str[i], pos));
		else if (ft_isredirections(str[i]) == 1)
			return (delimit_separator(str, i, str[i], pos));
		else if (str[i] == '=')
			return (delimit_separator(str, i, str[i], pos));
		else if (str[i] == '$')
			return (delimit_expand(str, i, pos));
		else if (str[i] == '\'' && quote_indication == 0)
			return (look_for_quote(str, i, '\'', pos));
		else if (str[i] == '\'' && quote_indication == 1)
			return (delimit_separator(str, i, str[i], pos));
		else if (str[i] == '"')
			return (look_for_quote(str, i, '"', pos));
		else if (ft_isspace(str[i]) == 1)
			return (delimit_separator(str, i, str[i], pos));
		i++;
	}
	return (i);
}

char	*find_lexeme(char *user_input, int starting_point, int *end,
	int quote_indication)
{
	char	*temp;
	int	beginning;

	beginning = ft_beginning_lexeme(user_input, starting_point,
			quote_indication);
	//printf("beginning = %d\n", beginning);
	*end = ft_end_lexeme(user_input, beginning, quote_indication);
	//printf("end = %d\n", *end);
	temp = ft_cut_str(user_input, beginning, *end);
	return (temp);
}

/*
 ** Scan the user_input to find lexeme delimited by whitespace, pipe, quote,
 ** redirections and put it into a linked list in the structure
 */

int		scanner(char *user_input, t_shell *shell)
{
	t_double_list	*list;
	int		end;
	char	*temp;

	temp = find_lexeme(user_input, 0, &end, 0);
	if (temp != NULL)
		list = ft_double_lstnew(temp);
	if (list == NULL)
	{
		g_signal = -1;
		return (g_signal);
	}
	while (end < (int)ft_strlen(user_input))
	{
		temp = find_lexeme(user_input, end, &end, 0);
		if (temp == NULL && g_signal == -1)
			return (g_signal);
		else if (temp == NULL)
			end++;
		if (temp != NULL)
			ft_double_lstadd_back(&list, ft_double_lstnew(temp));
	}
	shell->token = list;
	return (0);
}
