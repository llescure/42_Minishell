#include "../../include/minishell.h"

void	expand_expansion(t_shell *shell, t_double_list *type,
			t_double_list **list)
	{

		while (type != NULL && (*list)->next != NULL)
		{
			if (ft_strncmp(type->content, "expand", ft_strlen(type->content)) == 0)
				expansion_cases(shell, &(*list)->content);
			type = type->next;
			*list = (*list)->next;
		}
		if (ft_strncmp(type->content, "expand", ft_strlen(type->content)) == 0)
			expansion_cases(shell, &(*list)->content);
		while ((*list)->previous != NULL)
			*list = (*list)->previous;
	}

/*
 ** This function handles the 3 differences cases of expansion:
 ** - a ? which must be equal to our global variable to keep track of signals
 ** - an env variable that must be remplaced by the string from the env
 ** - None of the above which must be remplaced by an empty string
 ** It first splits the string to get words in a tab, replaces the word
 ** according to the 3 expansion cases and then join back the string
*/

void	expansion_cases(t_shell *shell, void **str)
	{
		char	*temp;
		char	**tab_for_quotes;
		char	*tab_joined;
		int	i;

		i = 0;
		tab_for_quotes = NULL;
		if (number_occurence_cara_in_str(*str, '\'') >= 2
				|| number_occurence_cara_in_str(*str, '"') >= 2)
			tab_for_quotes = ft_split_multiple_cara(*str, '\'', '"');
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

void	get_identifier(t_shell *shell, char **str)
{
		char	*temp;
		char	**tab;
		char	*tab_joined;
		int	i;

		i = 0;
		tab = ft_split(*str, '$');
		while (tab[i] != NULL)
		{
			temp = tab[i];
			if (tab[i][0] == '?')
				tab[i] = ft_itoa(g_signal);
			else if (expand_env_variable(tab[i], shell->env) != NULL)
				tab[i] = ft_strdup(expand_env_variable(tab[i], shell->env));
			else
				tab[i] = ft_strdup("");
			free(temp);
			i++;
		}
		tab_joined = ft_join_tab(tab);
		free_tab(tab);
		temp = *str;
		*str = tab_joined;
		free(temp);
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
						ft_strlen(variable_to_find)) == 0)
				return (env->tab_variable_equals[i]);
			i++;
		}
		return (NULL);
	}
