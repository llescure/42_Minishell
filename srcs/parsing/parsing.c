/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:23:17 by llescure          #+#    #+#             */
/*   Updated: 2022/04/21 17:00:07 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 ** Main function that 1) launches the scanner, 2) the lexer, 3) proceeds to
 ** expansions with $ and between quotes and 4) finally the grammatical check
 */

int	parsing(char *user_input, t_shell *shell)
{
	if (user_input[0] == '\0')
		return (0);
	if (scanner(user_input, shell) < 0)
		return (error_system(shell, MALLOC));
	if (tokenizer(shell->token, shell) < 0)
		return (error_system(shell, MALLOC));
	if (clean_input(shell) != 0)
		return (g_signal);
	if (join_clean_input(&shell->token) < 0)
		return (error_system(shell, MALLOC));
	transform_expand_quote_command(shell->token);
	find_word_in_token(shell->token);
	delete_empty_word(shell->token);
	delete_multiple_space(shell->token);
	if (look_for_grammar_error(shell->token) != 0)
		return (g_signal);
	if (initialization_command(shell->token, shell) < 0)
		return (error_system(shell, MALLOC));
	//print_token(shell->token);
	delete_redirection_in_token(&shell->token, shell, shell->command);
	delete_multiple_space(shell->token);
	delete_word_in_command(shell->token, shell->command);
//	print_token(shell->token);
	return (0);
}

/*
 * * This function checks if any error in the token was noticed +
 * * does quote and identifier expansion
*/

int	clean_input(t_shell *shell)
{
	if (look_for_word_in_type(shell->token, ERROR) == 1)
	{
		error_message(SYNTAX, 1);
		return (1);
	}
	if (look_for_word_in_type(shell->token, QUOTE) == 1)
		single_quote_expansion(shell, &shell->token);
	if (look_for_word_in_type(shell->token, D_QUOTE) == 1)
		double_quote_expansion(shell, &shell->token);
	if (look_for_word_in_type(shell->token, EXPAND) == 1)
		expand_expansion(shell, &shell->token);
	if (g_signal < 0)
		return (error_system(shell, MALLOC));
	return (0);
}

/*
 * * This function joins the node of the linked list after expansion.
 * * Nodes are joined if the current node is 1) a word, 2) a single_quote,
 * * 3) a double quote, 4) an identifier and the next node if one of the 4 types
*/

int	join_clean_input(t_token **token)
{
	while ((*token)->next != NULL)
	{
		if (check_special_condition_cara((*token)->type) == 1)
			join_quote_word_expand(token);
		if ((*token)->next == NULL)
			break ;
		*token = (*token)->next;
	}
	while ((*token)->previous != NULL)
		*token = (*token)->previous;
	return (0);
}

int	look_for_grammar_error(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == PIPE)
		{
			token = token->next;
			while (token != NULL && token->type == WHITE_SPACE)
				token = token->next;
			if (token == NULL)
			{
				error_message(SYNTAX, 1);
				return (g_signal);
			}
			else if (token->type == PIPE)
			{
				error_message(SYNTAX, 1);
				return (g_signal);
			}
		}
		token = token->next;
	}
	return (0);
}
