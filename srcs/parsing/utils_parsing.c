#include "../../include/minishell.h"

int		special_condition_cara_is_respected(int type)
{
	if (type == QUOTE || type == WORD || type = D_QUOTE || type == EXPAND)
		return (1);
	return (0);
}

int		look_for_word_in_type(t_double_list *list, int type)
{
	while (list != NULL)
	{
		if (list->content == type)
			return (1);
		list = list->next;
	}
	return (0);
}
