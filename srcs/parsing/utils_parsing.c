#include "../../include/minishell.h"

int		special_condition_cara_is_respected(char *str)
{
	if (ft_strncmp(str, "single_quote", ft_strlen(str)) == 0
			|| ft_strncmp(str, "word", ft_strlen(str)) == 0
			|| ft_strncmp(str, "double_quote", ft_strlen(str)) == 0
			|| ft_strncmp(str, "expand", ft_strlen(str)) == 0)
		return (1);
	return (0);
}

int		look_for_word_in_type(t_double_list *list, char *str)
{
	while (list != NULL)
	{
		if (ft_strncmp(list->content, str, ft_strlen(str)) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}
