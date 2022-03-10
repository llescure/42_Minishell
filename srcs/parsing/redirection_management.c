#include "../../include/minishell.h"

int		attach_redirections_to_command(t_command *command, t_type *type,
		t_double_list *token)
{
	t_redirection	*redirection;

	redirection = NULL;
	look_for_redirection_before_command(command, type, token, &redirection);
	look_for_redirection_after_command(command, type, token, &redirection);
	if (g_signal == -1)
		return (g_signal);
	command->redirection = redirection;
	return (0);
}

void	look_for_redirection_before_command(t_command *command, t_type *type,
		t_double_list *token, t_redirection **redirection)
{
	int	compt;

	compt = 0;
	while (type != NULL && compt != command->id)
	{
		type = type->next;
		compt++;
	}
	while (type != NULL && type->content != PIPE && token != NULL)
	{
		if (type->content == REDIR_RIGHT || type->content == REDIR_LEFT
				|| type->content == HEREDOC || type->content == D_REDIR_RIGHT)
		{
			if (*redirection == NULL)
			{
				*redirection = create_redirection_struct(token->content,
						type->content);
				if (*redirection == NULL)
					return (error_message(MALLOC, 1));
			}
			else
				append_redirection_struct(redirection, token->content,
						type->content);
		}
		type = type->previous;
		token = token->previous;
	}
}

void	look_for_redirection_after_command(t_command *command, t_type *type,
		t_double_list *token, t_redirection **redirection)
{
	int	compt;

	compt = 0;
	while (type != NULL && compt != command->id)
	{
		type = type->next;
		compt++;
	}
	while (type != NULL && type->content != PIPE && token != NULL)
	{
		if (type->content == REDIR_RIGHT || type->content == REDIR_LEFT
			   	|| type->content == HEREDOC || type->content == D_REDIR_RIGHT)
		{
			if (*redirection == NULL)
			{
				*redirection = create_redirection_struct(token->content,
						type->content);
				if (*redirection == NULL)
					return (error_message(MALLOC, 1));
			}
			else
			{
				append_redirection_struct(redirection, token->content,
						type->content);
			}
		}
		type = type->next;
		token = token->next;
	}
}

t_redirection	*create_redirection_struct(char *str, t_category category)
{
	t_redirection	*redirection;

	redirection = malloc(sizeof(*redirection));
	if (redirection == NULL)
		return (NULL);
	if (category == REDIR_RIGHT || category == D_REDIR_RIGHT)
		redirection->file = find_file_for_redir(str, '>');
	else if (category == REDIR_LEFT || category == HEREDOC)
		redirection->file = find_file_for_redir(str, '<');
	redirection->category = category;
	redirection->next = NULL;
	return (redirection);
}

char	*find_file_for_redir(char	*str, char redir)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && (str[i] == redir || ft_isspace(str[i]) == 1))
		i++;
	return(&str[i]);
}

int		append_redirection_struct(t_redirection **redirection, char *str,
		t_category category)
{
	t_redirection	*temp;

	temp = *redirection;
	while((temp)->next != NULL)
		temp = temp->next;
	temp->next = create_redirection_struct(str, category);
	if (temp->next == NULL)
	{
		error_message(MALLOC, 1);
		return(-1);
	}
	return (0);
}

void	print_redirection(t_redirection	*redirection)
{
	int	compt;

	compt = 0;
	if (redirection == NULL)
		return ;
	while (redirection->next != NULL)
	{
		printf("compt = %d content = %s\n", compt, (*redirection).file);
		compt++;
		redirection = redirection->next;
	}
	printf("compt = %d content = %s\n", compt, (*redirection).file);
}
