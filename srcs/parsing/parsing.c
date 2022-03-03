#include "../../include/minishell.h"

/*
 ** Main function that 1) launches the scanner, 2) the lexer, 3) proceeds to
 ** expansions with $ and between quotes and 4) finally the grammatical check
 */

int		parsing(char *user_input, t_shell *shell)
{
	shell->command_count = 0;
	if (user_input[0] == '\0')
		return (0);
	if (scanner(user_input, shell) < 0)
		return (error_malloc(shell));
	if (tokenizer(shell->token, shell) < 0)
		return (error_malloc(shell));
//	ft_double_print_list(shell->token);
//	ft_double_print_list(shell->type);
	if (check_and_expand_input(shell) != 0)
		return (g_signal);
//	printf("\n");
	if (join_clean_input(&shell->token, shell->type) < 0)
		return (error_malloc(shell));
	ft_double_free_list(&shell->type, 0);
	if (tokenizer(shell->token, shell) < 0)
		return (error_malloc(shell));
	ft_double_print_list_char(shell->token);
	ft_double_print_list_int(shell->type);
	look_for_grammar_error(shell->type, shell->fd_outfile, shell);
	return (0);
}

/*
 * * This function checks if any error in the token was noticed +
 * * does quote and identifier expansion
*/

int		check_and_expand_input(t_shell *shell)
{
	if (look_for_word_in_type(shell->type, ERROR) == 1)
	{
		error_message("syntax", shell->fd_outfile);
		return (g_signal);
	}
	if (look_for_word_in_type(shell->type, QUOTE) == 1)
		single_quote_expansion(shell, shell->type, &shell->token);
	if (look_for_word_in_type(shell->type, D_QUOTE) == 1)
		double_quote_expansion(shell, shell->type, &shell->token);
	if (look_for_word_in_type(shell->type, EXPAND) == 1)
		expand_expansion(shell, shell->type, &shell->token);
	if (g_signal < 0)
		return(error_malloc(shell));
	return (0);
}

/*
 * * This function joins the node of the linked list after expansion.
 * * Nodes are joined if the current node is 1) a word, 2) a single_quote,
 * * 3) a double quote, 4) an identifier and the next node if one of the 4 types
*/

int		join_clean_input(t_double_list **token, t_double_list *type)
{
	char	*str_temp;

	while (type->next != NULL)
	{
		if (special_condition_cara_is_respected(type->content) == 1)
		{
			while (type->next != NULL &&
				special_condition_cara_is_respected(type->next->content) == 1)
			{
				str_temp = (*token)->content;
				(*token)->content = ft_strjoin(str_temp, (*token)->next->content);
				free(str_temp);
				delete_node(token, 1);
				delete_node(&type, 0);
			}
		}
		if (type->next == NULL)
			break;
		if (type->content == WHITE_SPACE)
		{
			str_temp = (*token)->content;
			(*token)->content = ft_strdup(" ");
			free(str_temp);
		}
		type = type->next;
		*token = (*token)->next;
	}
	while ((*token)->previous != NULL)
		*token = (*token)->previous;
	return (0);
}

void	look_for_grammar_error(t_double_list *type, int fd_outfile,
		t_shell *shell)
{
	if (look_for_word_in_type(type, HEREDOC) == 0 &&
		(type->content == COMMAND_OPTION || type->content == WORD
		 || type->content == EXPAND))
	{
		shell->command_count++;
		return (error_message("command", fd_outfile));
	}
	else if ((type->content == REDIR_RIGHT || type->content == REDIR_LEFT
		|| type->content == HEREDOC || type->content == D_REDIR_RIGHT)
		&& type->next == NULL)
		return (error_message("syntaxe", fd_outfile));
	else if (type->content == PIPE)
		return (error_message("syntaxe", fd_outfile));
}

char	**create_tab_from_linked_list(t_double_list *list)
{
	char	**tab_cpy;
	int		i;

	tab_cpy = malloc(sizeof(char *) * (ft_double_lstsize(list) + 1));
	if (tab_cpy == NULL)
		return (NULL);
	i = 0;
	while (list != NULL)
	{
		tab_cpy[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	tab_cpy[i] = NULL;
	return (tab_cpy);
}
