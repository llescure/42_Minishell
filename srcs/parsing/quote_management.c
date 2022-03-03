#include "../../include/minishell.h"

void	single_quote_expansion(t_shell *shell, t_double_list *type,
		t_double_list **token)
{
	quote_expansion(shell, type, token, '\'', QUOTE);
}

void	double_quote_expansion(t_shell *shell, t_double_list *type,
		t_double_list **token)
{
	quote_expansion(shell, type, token, '"', D_QUOTE);
}

/*
 ** This function spots all the occurence of quotes in the user_input string,
 ** creates new strings without the quote and makes sure that everything is
 ** freed. It also makes sure that there is not other expansion character.
 */

void	quote_expansion(t_shell *shell, t_double_list *type,
		t_double_list **token, char type_cara_to_delete, int type_expansion)
{

	while (type != NULL && (*token)->next != NULL)
	{
		if (type->content == type_expansion,
			quote_cases(shell, (char **)&(*token)->content, type_cara_to_delete);
		type = type->next;
		*token = (*token)->next;
	}
	if (type->content == type_expansion)
		quote_cases(shell, (char **)&(*token)->content, type_cara_to_delete);
	while ((*token)->previous != NULL)
		*token = (*token)->previous;
}


void	quote_cases(t_shell *shell, char **str, char type_cara_to_delete)
{
	char	*temp;

	if (type_cara_to_delete == '"' &&
			find_cara_in_word(*str, '$') >= 0)
		expansion_cases(shell, (void **)str);
	temp = *str;
	*str = remove_cara(*str, type_cara_to_delete);
	free(temp);
}

char	*remove_cara(char *str, char type_cara_to_delete)
{
	char	*cpy;
	int	nbr_occurence;

	nbr_occurence = number_occurence_cara_in_str(str, type_cara_to_delete);
	cpy = malloc(sizeof(char) * (ft_strlen(str) - nbr_occurence + 1));
	if (cpy == NULL)
		return (NULL);
	ft_strlcpy_without_cara(cpy, str, type_cara_to_delete);
	return (cpy);
}
