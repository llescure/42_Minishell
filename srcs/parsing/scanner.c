#include "../../include/minishell.h"

int	ft_beginning_lexeme(char *str, int pos)
{
	int	i;

	i = pos;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (ft_iscara(str[i], '\'') == 1)
	{
		if (look_for_quote(str, i, '\'') == i + 1)
			return (look_for_quote(str, i, '\''));
	}
	else if (ft_iscara(str[i], '"') == 1)
	{
		if (look_for_quote(str, i, '"') == i + 1)
			return (look_for_quote(str, i, '"'));
	}
	return (i);
}

int	delimit_separator(char *str, int pos, char separator, int initial_pos)
{
	int	i;
	int	first_true;

	first_true = 0;
	i = pos;
	if (pos > 0 && (pos - 1 == 0 || ft_iscara(str[pos - 1], separator) == 0))
		first_true = 1;
	i++;
	while (ft_iscara(str[i], separator) == 1 && str[i] != '\0')
		i++;
	if (first_true == 1 && ft_isspace(str[pos - 1]) == 0 && i - 2 > initial_pos)
		return (pos);
	return (i);
}

int	ft_end_lexeme(char *str, int pos)
{
	int	i;

	i = pos;
	while (ft_isspace(str[i]) == 0 && str[i] != '\0')
	{
		if (ft_iscara(str[i], '|') == 1)
			return (delimit_separator(str, i, str[i], pos));
		else if (ft_isredirections(str[i]) == 1)
			return (delimit_separator(str, i, str[i], pos));
		i++;
	}
	return (i);
}

/*
 ** When a single quote or double quote is encountered this function looks for
 ** the next one. If none were found, the quote is skipped
 */

int	look_for_quote(char *str, int pos, char type_quote)
{
	int	i;

	i = pos;
	i++;
	while (ft_iscara(str[i], type_quote) == 0 && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (pos + 1);
	return (i + 1);
}

char	*ft_cut_str(char *user_input, int beginning, int end)
{
	char	*new_str;
	int		i;
	int		j;

	i = beginning;
	j = 0;
	if (end - beginning <= 0)
		return (NULL);
	new_str = malloc(sizeof(char) * end - beginning + 1);
	if (new_str == NULL)
	{
		g_signal = -1;
		return (new_str);
	}
	while ( j < end - beginning && user_input[i] != '\0')
	{
		new_str[j] = user_input[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*find_lexeme(char *user_input, int starting_point, int *end)
{
	char	*temp;
	int	beginning;

	beginning = ft_beginning_lexeme(user_input, starting_point);
	*end = ft_end_lexeme(user_input, beginning);
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
