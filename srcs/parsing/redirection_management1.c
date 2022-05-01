/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:01:57 by llescure          #+#    #+#             */
/*   Updated: 2022/05/01 18:56:03 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	attach_redirections_to_command(t_command *command, t_token *token)
{
	t_redirection	*redirection;

	redirection = NULL;
	if (token->previous != NULL)
		look_for_redirection_before_command(token, &redirection);
	look_for_redirection_after_command(token, &redirection);
	if (g_signal == -1)
		return (g_signal);
	command->redirection = redirection;
	return (0);
}

void	look_for_redirection_before_command(t_token *token,
		t_redirection **redirection)
{
	token = token->previous;
	while (token != NULL && token->type != PIPE && token->type != COMMAND)
	{
		if (token->type == REDIR_RIGHT || token->type == REDIR_LEFT
			|| token->type == HEREDOC || token->type == D_REDIR_RIGHT)
		{
			if (*redirection == NULL)
			{
				*redirection = create_redirection_struct(token->content,
						token->type);
				if (*redirection == NULL)
					return (error_message(MALLOC, 1));
			}
			else
				append_redirection_struct(redirection, token->content,
					token->type);
		}
		token = token->previous;
	}
}

void	look_for_redirection_after_command(t_token *token,
		t_redirection **redirection)
{
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == REDIR_RIGHT || token->type == REDIR_LEFT
			|| token->type == HEREDOC || token->type == D_REDIR_RIGHT)
		{
			if (*redirection == NULL)
			{
				*redirection = create_redirection_struct(token->content,
						token->type);
				if (*redirection == NULL)
					return (error_message(MALLOC, 1));
			}
			else
			{
				append_redirection_struct(redirection, token->content,
					token->type);
			}
		}
		token = token->next;
	}
}

void	delete_redirection_in_token(t_token **token, t_shell *shell,
		t_command *command)
{
	if (check_lonely_redirection(*token, shell, command) > 0)
		return ;
	while ((*token)->next != NULL)
	{
		while ((*token)->next != NULL && ((*token)->type == REDIR_RIGHT
				|| (*token)->type == REDIR_LEFT
				|| (*token)->type == D_REDIR_RIGHT
				|| (*token)->type == HEREDOC))
			(*token)->type = EMPTY;
		if ((*token)->next == NULL)
			break ;
		*token = (*token)->next;
	}
	if ((*token)->type == REDIR_RIGHT || (*token)->type == REDIR_LEFT
		|| (*token)->type == D_REDIR_RIGHT || (*token)->type == HEREDOC)
			(*token)->type = EMPTY;
	while ((*token)->previous != NULL)
		*token = (*token)->previous;
}

int	check_lonely_redirection(t_token *token, t_shell *shell, t_command *command)
{
	t_redirection	*redir;
	int				return_value;

	if (command != NULL)
		return (0);
	redir = NULL;
	while (token != NULL && (token->type == REDIR_RIGHT
			|| token->type == REDIR_LEFT || token->type == HEREDOC
			|| token->type == D_REDIR_RIGHT || token->type == WHITE_SPACE))
	{
		if (redir == NULL && (token->type == REDIR_LEFT
				|| token->type == REDIR_RIGHT
				|| token->type == HEREDOC || token->type == D_REDIR_RIGHT))
			redir = create_redirection_struct(token->content, token->type);
		else if (redir != NULL && token->type != WHITE_SPACE)
			append_redirection_struct(&redir, token->content, token->type);
		token = token->next;
	}
	return_value = check_creation_file(redir, shell, token, command);
	if (return_value != 42)
		return (return_value);
	initialize_redir(shell);
	reset_fd(shell);
	free_redirection(&redir);
	return (1);
}
