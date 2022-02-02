#include "../../include/minishell.h"

int	ft_beginning_token(char const *s, int pos)
{
	int	i;

	i = pos;
	while (ft_isspace(s[i]) == 1)
		i++;
	return (i);
}

int	ft_end_token(char const *s, int pos)
{
	int	i;

	i = pos;
	while (ft_isspace(s[i]) == 0 && s[i] != '\0')
		i++;
	return (i);
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

int		ft_split_linked_list(char *user_input, t_shell *shell)
{
	t_list	*list;
	int		beginning;
	int		end;
	char	*temp;

	beginning = ft_beginning_token(user_input, 0);
	end = ft_end_token(user_input, beginning);
	temp = ft_cut_str(user_input, beginning, end);
	list = ft_lstnew(temp);
	if (list == NULL)
	{
		g_signal = -1;
		return (g_signal);
	}
	while (end != (int)ft_strlen(user_input))
	{
		beginning = ft_beginning_token(user_input, end);
		end = ft_end_token(user_input, beginning);
		temp = ft_cut_str(user_input, beginning, end);
		if (temp == NULL && g_signal == -1)
			return (g_signal);
		ft_lstadd_back(&list, ft_lstnew(temp));
	}
	shell->token = list;
}
