#include "../../include/minishell.h"

int	ft_beginning_lexeme(char *str, int pos)
{
	int	i;

	i = pos;
	while (ft_isspace(str[i]) == 1)
		i++;
	return (i);
}

int	ft_end_lexeme(char *str, int pos)
{
	int	i;

	i = pos;
	while (ft_isspace(str[i]) == 0 && str[i] != '\0' &&
			ft_iscara(str[i], '|') == 0 && ft_isredirections(str[i]) == 0)
	{
		if (ft_iscara(str[i], '\'') == 1)
				return (look_for_quote(str, i, '\''));
		else if (ft_iscara(str[i], '"') == 1)
				return (look_for_quote(str, i, '"'));
		i++;
	}
	return (i);
}

int	look_for_quote(char *str, int pos, char type_quote)
{
	int	i;

	i = pos;
	i++;
	while (ft_iscara(str[i], type_quote) == 0 && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (pos);
	return (i + 1);
}

char	*ft_cut_str(char *user_input, int beginning, int end)
{
	char	*new_str;
	int		i;
	int		j;

	i = beginning;
	j = 0;
	new_str = malloc(sizeof(char) * end - beginning + 1);
	if (new_str == NULL)
	{
		g_signal = -1;
		return (new_str);
	}
	if (end - beginning <= 0)
		return (NULL);
	while ( j < end - beginning && user_input[i] != '\0')
	{
		new_str[j] = user_input[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int		scanner(char *user_input, t_shell *shell)
{
	t_list	*list;
	int		beginning;
	int		end;
	char	*temp;

	beginning = ft_beginning_lexeme(user_input, 0);
	end = ft_end_lexeme(user_input, beginning);
	temp = ft_cut_str(user_input, beginning, end);
	if (temp != NULL)
		list = ft_lstnew(temp);
	if (list == NULL)
	{
		g_signal = -1;
		return (g_signal);
	}
	while (end <= (int)ft_strlen(user_input))
	{
		beginning = ft_beginning_lexeme(user_input, end);
		printf("beginning = %d\n", beginning);
		end = ft_end_lexeme(user_input, beginning);
		printf("end = %d\n", end);
		temp = ft_cut_str(user_input, beginning, end);
		if (temp == NULL && g_signal == -1)
			return (g_signal);
		if (temp != NULL)
			ft_lstadd_back(&list, ft_lstnew(temp));
	}
	shell->token = list;
	return (0);
}
