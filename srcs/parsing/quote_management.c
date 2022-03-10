/*#include "../../include/minishell.h"

void	single_quote_expansion(t_shell *shell, t_type *type,
		t_double_list **token)
{
	quote_expansion(shell, type, token, QUOTE);
}

void	double_quote_expansion(t_shell *shell, t_type *type,
		t_double_list **token)
{
	quote_expansion(shell, type, token, D_QUOTE);
}*/

/*
 ** This function spots all the occurence of quotes in the user_input string,
 ** creates new strings without the quote and makes sure that everything is
 ** freed. It also makes sure that there is not other expansion character.
 */

/*void	quote_expansion(t_shell *shell, t_type *type,
		t_double_list **token, t_category category_expansion)
{

	while (type != NULL && (*token)->next != NULL)
	{
		if (type->content == category_expansion)
			quote_cases(shell, (char **)&(*token)->content, category_expansion);
		type = type->next;
		*token = (*token)->next;
	}
	if (type->content == category_expansion)
		quote_cases(shell, (char **)&(*token)->content, category_expansion);
	while ((*token)->previous != NULL)
		*token = (*token)->previous;
}


void	quote_cases(t_shell *shell, char **str, t_category category_expansion)
{
	char	*temp;

	if (category_expansion == D_QUOTE &&
			find_cara_in_word(*str, '$') >= 0)
		expansion_cases(shell, (void **)str);
	temp = *str;
	if (category_expansion == D_QUOTE)
		*str = remove_cara(*str, '"');
	else
		*str = remove_cara(*str, '\'');
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
}*/
