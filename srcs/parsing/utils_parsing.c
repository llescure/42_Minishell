#include "../../include/minishell.h"

int		special_condition_cara_is_respected(t_category category)
{
	if (category == QUOTE || category == WORD || category == D_QUOTE ||
			category == EXPAND)
		return (1);
	return (0);
}

int		look_for_word_in_type(t_type *type, t_category category)
{
	while (type != NULL)
	{
		if (type->content == category)
			return (1);
		type = type->next;
	}
	return (0);
}
