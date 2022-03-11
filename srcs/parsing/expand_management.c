#include "../../include/minishell.h"

void	expand_expansion(t_shell *shell, t_token **token)
{

	while ((*token)->next != NULL)
	{
		if ((*token)->type == EXPAND)
			expansion_cases(shell, &(*token)->content);
		*token = (*token)->next;
	}
	if ((*token)->type == EXPAND)
		expansion_cases(shell, &(*token)->content);
	while ((*token)->previous != NULL)
		*token = (*token)->previous;
}

/*
 ** This function evaluates if the string has double quotes or just an
 ** identifier and treats the string accordingly. It joins the created tab with
 ** the different double quoted part at the end
 */

void	expansion_cases(t_shell *shell, char **str)
{
	char	*temp;
	char	**tab_for_quotes;
	char	*tab_joined;
	int	i;

	i = 0;
	tab_for_quotes = NULL;
	if (number_occurence_cara_in_str(*str, '"') >= 2)
		tab_for_quotes = ft_split(*str, '"');
	if (tab_for_quotes == NULL)
		get_identifier(shell, (char **)str);
	else
	{
		while (tab_for_quotes[i] != NULL)
		{
			if (find_cara_in_word(tab_for_quotes[i], '$') >= 0)
				get_identifier(shell, &tab_for_quotes[i]);
			i++;
		}
		tab_joined = ft_join_tab(tab_for_quotes);
		free_tab(tab_for_quotes);
		temp = *str;
		*str = tab_joined;
		free(temp);
	}
}

/*
 ** This function handles the different cases of expansion:
 ** - a ? which must be equal to our global variable to keep track of signals
 ** - an env variable that must be remplaced by the string from the env
 ** - a simple $ which must be equal to a $
 ** - a string before the $ which must be the same litteral value
 ** - None of the above which must be remplaced by an empty string
 ** It first splits the string to get words in a tab, deletes the identifier and
 ** replaces the word according to the expansion cases and then
 ** join back the string
 */

void	get_identifier(t_shell *shell, char **str)
{
	char	*temp;
	char	*temp2;
	char	**tab;
	char	*tab_joined;
	int	i;

	i = 0;
	tab = split_expand(*str, '$');
	temp2 = NULL;
	while (tab[i] != NULL)
	{
		temp = tab[i];
		identifier_cases(&tab[i], temp, temp2, shell);
		free(temp);
		i++;
	}
	tab_joined = ft_join_tab(tab);
	free_tab(tab);
	temp = *str;
	*str = tab_joined;
	free(temp);
}

void	identifier_cases(char **str_to_change, char *original_str, char *temp2,
		t_shell *shell)
{
	if (find_cara_in_word(*str_to_change, '$') > -1)
	{
		*str_to_change = remove_cara(*str_to_change, '$');
		temp2 = *str_to_change;
	}
	if (original_str[0] == '$' && *str_to_change[0] == '?')
		*str_to_change = ft_itoa(g_signal);
	else if (original_str[0] == '$' && *str_to_change[0] == '\0')
		*str_to_change = ft_strdup("$");
	else if (original_str[0] == '$'
			&& expand_env_variable(*str_to_change, shell->env) != NULL)
		*str_to_change = ft_strdup(expand_env_variable(*str_to_change,
					shell->env));
	else if (original_str[0] != '$')
		*str_to_change = ft_strdup(*str_to_change);
	else
		*str_to_change = ft_strdup("");
	if (temp2 != NULL)
		free(temp2);
}

/*
 ** This function checks if the variable given in parameter actually exists
 ** inside the environment varianle. If this is the case it returns what this
 ** env variable is equal inside env
 */

char	*expand_env_variable(char *variable_to_find, t_env *env)
{
	int	i;

	i = 0;
	while (i < env->index)
	{
		if (ft_strncmp(env->tab_variable_name[i], variable_to_find,
					ft_strlen(env->tab_variable_name[i])) == 0
				&& ft_strncmp(env->tab_variable_name[i], variable_to_find,
					ft_strlen(variable_to_find)) == 0)
			return (env->tab_variable_equals[i]);
		i++;
	}
	return (NULL);
}

/*
 ** This function splits the string into a tab if it encounters a $
 ** or simple quote
 */

char	**split_expand(char *str, char cara)
{
	int		j;
	int		i;
	char	**tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (ft_count_words_multiple(str, cara, '\'')
				+ 2));
	if (tab == NULL)
	{
		g_signal = -1;
		return (NULL);
	}
	while (str[i] != '\0')
	{
		tab[j] = find_lexeme(str, i, &i, 1);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
