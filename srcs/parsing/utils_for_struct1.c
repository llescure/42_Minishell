#include "../../include/minishell.h"

t_token	*new_token(t_type type, char *content, int id)
{
	t_token *new_token;

	if (!(new_token = malloc(sizeof(*new_token))))
		return (NULL);
	new_token->type = type;
	new_token->content = content;
	new_token->id = id;
	new_token->next = NULL;
	new_token->previous = NULL;
	return (new_token);
}

void	add_back_token(t_token **token, t_token *new)
{
	t_token *temp;

	if (token == NULL)
		return ;
	new->next = NULL;
	temp = *token;
	if (temp == NULL)
	{
		new->previous = NULL;
		temp = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	new->previous = temp;
	temp->next = new;
}

void	free_token(t_token **token)
{
	t_token	*temp;

	if (*token == NULL || token == NULL)
		return ;
	while ((*token)->next != NULL)
	{
		temp = (*token)->next;
		free((*token)->content);
		free(*token);
		*token = temp;
	}
	free((*token)->content);
	free(*token);
	*token = NULL;
}

void	print_token(t_token *token)
{
	if (token == NULL)
		return ;
	while (token->next != NULL)
	{
		printf("compt = %d type = %d content = %s\n", (*token).id,
				(int)(*token).type, (*token).content);
		token = token->next;
	}
	printf("compt = %d type = %d content = %s\n", (*token).id,
			(int)(*token).type, (*token).content);
}
