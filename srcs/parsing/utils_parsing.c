#include "../../include/minishell.h"

int		special_condition_cara_is_respected(t_type type)
{
	if (type == QUOTE || type == WORD || type == D_QUOTE ||
			type == EXPAND)
		return (1);
	return (0);
}

int		look_for_word_in_type(t_token *token, t_type type)
{
	while (token != NULL)
	{
		if (token->type == type)
			return (1);
		token = token->next;
	}
	return (0);
}
