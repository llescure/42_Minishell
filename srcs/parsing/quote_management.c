#include "../../include/minishell.h"

void	single_quote_expansion(t_shell *shell, t_double_list *type,
		t_double_list **list)
{
	quote_expansion(shell, type, list, '\'', "single_quote");
}

void	double_quote_expansion(t_shell *shell, t_double_list *type,
		t_double_list **list)
{
	quote_expansion(shell, type, list, '"', "double_quote");
}

/*
 ** This function spots all the occurence of quotes in the user_input string,
 ** creates new strings without the quote and makes sure that everything is
 ** freed. It also makes sure that there is not other expansion character.
 */

void	quote_expansion(t_shell *shell, t_double_list *type,
		t_double_list **list, char type_cara_to_delete, char *type_expansion)
{

	while (type != NULL && (*list)->next != NULL)
	{
		if (ft_strncmp(type->content, type_expansion,
					ft_strlen(type->content)) == 0)
			quote_cases(shell, (char **)&(*list)->content, type_cara_to_delete);
		type = type->next;
		*list = (*list)->next;
	}
	if (ft_strncmp(type->content, type_expansion,
				ft_strlen(type->content)) == 0)
			quote_cases(shell, (char **)&(*list)->content, type_cara_to_delete);
	while ((*list)->previous != NULL)
		*list = (*list)->previous;
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
