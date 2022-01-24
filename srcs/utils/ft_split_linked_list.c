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
	int	compt;

	i = pos;
	compt = 0;
	while (ft_isspace(s[i]) == 1)
		i++;
	while (ft_isspace(s[i]) == 0 && s[i] != '\0')
	{
		compt++;
		i++;
	}
	return (compt);
}

char	*ft_cut_str(char *user_input, int beginning, int end)
{
	char	*new_str;
	int		i;

	i = beginning;
	new_str = malloc(sizeof(char) * end - beginning + 1);
	while ( i < end && user_input[i] != '\0')
	{
		new_str[i] = user_input[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

void	ft_split_linked_list(char *user_input, t_shell *shell)
{
	t_list	*list;
	int		beginning;
	int		end;
	char	*temp;

	beginning = ft_beginning_token(user_input, 0);
	end = ft_end_token(user_input, beginning);
	temp = ft_cut_str(user_input, beginning, end);
	list = ft_lstnew(temp);
	//free(temp);
	while (end != (int)ft_strlen(user_input))
	{
		beginning = ft_beginning_token(user_input, end);
		end = ft_end_token(user_input, beginning);
		temp = ft_cut_str(user_input, beginning, end);
		ft_lstadd_back(&list, ft_lstnew(temp));
	}
	shell->token = list;
}
