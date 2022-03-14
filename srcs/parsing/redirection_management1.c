#include "../../include/minishell.h"

int		attach_redirections_to_command(t_command *command, t_token *token)
{
	t_redirection	*redirection;

	redirection = NULL;
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

void	delete_redirection_in_token(t_token **token)
{
	while ((*token)->next != NULL)
	{
		while ((*token)->next != NULL && ((*token)->type == REDIR_RIGHT
			|| (*token)->type == REDIR_LEFT || (*token)->type == D_REDIR_RIGHT
			|| (*token)->type == HEREDOC))
		{
			if ((*token)->id == 0)
				delete_first_token_node(token);
			else
				delete_token_node(token);
		}
		if ((*token)->next == NULL)
			break;
		*token = (*token)->next;
	}
	if ((*token)->type == REDIR_RIGHT || (*token)->type == REDIR_LEFT
		|| (*token)->type == D_REDIR_RIGHT || (*token)->type == HEREDOC)
		delete_last_token_node(token);
	while ((*token)->previous != NULL)
		*token = (*token)->previous;
}
