#include "../../include/minishell.h"

void	delete_token_node(t_token **token)
{
	t_token	*temp;

	temp = (*token)->next;
	(*token)->next = temp->next;
	if ((*token)->next != NULL)
		(*token)->next->previous = temp->previous;
	free(temp->content);
	free(temp);
}

void	delete_last_token_node(t_token **token)
{
	t_token	*temp;

	temp = *token;
	*token = (*token)->previous;
	(*token)->next = NULL;
	free(temp->content);
	free(temp);
}

void	delete_first_token_node(t_token **token)
{
	t_token	*temp;

	temp = *token;
	*token = (*token)->next;
	(*token)->previous = NULL;
	free(temp->content);
	free(temp);
}
