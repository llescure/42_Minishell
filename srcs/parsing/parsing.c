/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:23:17 by llescure          #+#    #+#             */
/*   Updated: 2022/04/11 12:23:24 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 ** Main function that 1) launches the scanner, 2) the lexer, 3) proceeds to
 ** expansions with $ and between quotes and 4) finally the grammatical check
 */

int	parsing(char *user_input, t_shell *shell)
{
	shell->command_count = 0;
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
	if (tokenizer(shell->token, shell) < 0)
		return (error_system(shell, MALLOC));
	if (look_for_grammar_error(shell->token, shell) != 0)
		return (g_signal);
	if (initialization_command(shell->token, shell) < 0)
		return (error_system(shell, MALLOC));
	delete_redirection_in_token(&shell->token);
//	print_token(shell->token);
	return (0);
}

/*
 * * This function checks if any error in the token was noticed +
 * * does quote and identifier expansion
*/

int	clean_input(t_shell *shell)
{
	unlink(shell->path_in);
	unlink(shell->path_out);
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
	char	*str_temp;

	while ((*token)->next != NULL)
	{
		if (check_special_condition_cara((*token)->type) == 1)
			join_quote_word_expand(token);
		if ((*token)->next == NULL)
			break ;
		if ((*token)->type == WHITE_SPACE)
		{
			str_temp = (*token)->content;
			(*token)->content = ft_strdup(" ");
			free(str_temp);
		}
		*token = (*token)->next;
	}
	while ((*token)->previous != NULL)
		*token = (*token)->previous;
	return (0);
}

int	look_for_grammar_error(t_token *token, t_shell *shell)
{
	if (look_for_word_in_type(token, HEREDOC) == 0
		&& (token->type == COMMAND_OPTION || token->type == WORD
			|| token->type == EXPAND))
	{
		shell->command_count++;
		error_message(COMMAND_ERROR, 1);
		return (g_signal);
	}
	else if ((token->type == REDIR_RIGHT || token->type == REDIR_LEFT
			|| token->type == HEREDOC || token->type == D_REDIR_RIGHT)
		&& token->next == NULL)
	{
		error_message(SYNTAX, 1);
		return (g_signal);
	}
	else if (token->type == PIPE && token->next == NULL)
	{
		error_message(SYNTAX, 1);
		return (g_signal);
	}
	return (0);
}
