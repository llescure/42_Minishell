#include "../../include/minishell.h"

void	ft_export(t_shell *shell, t_token **token)
{
	*token = (*token)->next;
	if (export_without_argument(shell, *token) == 1)
		return ;
	while (*token != NULL && ((*token)->type == WHITE_SPACE
			|| (*token)->type == WORD || (*token)->type == COMMAND
			|| (*token)->type == EQUAL))
	{
		if ((*token)->type == WORD || (*token)->type == COMMAND)
		{
			if ((*token)->next == NULL)
				return (create_lonely_env_variable(shell, *token));
			*token = (*token)->next;
			if ((*token)->type == WHITE_SPACE && (*token)->next != NULL
					&& (*token)->next->type == EQUAL)
				return(error_message(EXPORT_ERROR, 1));
			else if ((*token)->type == WHITE_SPACE)
				create_lonely_env_variable(shell, *token);
			else if ((*token)->type == EQUAL)
				create_new_env_variable(shell, token);
		}
		else if ((*token)->type == EQUAL)
			return (error_message(EXPORT_ERROR, 1));
		if (*token == NULL)
			break ;
		*token = (*token)->next;
	}
}

void	create_lonely_env_variable(t_shell *shell, t_token *token)
{
	char	*new_env_variable;

	if (token->next != NULL)
		token = token->previous;
	if (check_if_variable_already_exists(shell, token->content) == 1)
		return ;
	new_env_variable = ft_strdup(token->content);
	add_new_env_variable(new_env_variable, shell);
}

void	create_new_env_variable(t_shell *shell, t_token **token)
{
	char	*new_env_variable;
	char	*temp;

	*token = (*token)->previous;
	new_env_variable = ft_strdup((*token)->content);
	*token = (*token)->next;
	while (*token != NULL)
	{
		if ((*token)->type == PIPE || (*token)->type == REDIR_LEFT
			|| (*token)->type == REDIR_RIGHT || (*token)->type == HEREDOC
			|| (*token)->type == D_REDIR_RIGHT || (*token)->type == WHITE_SPACE)
			break;
		temp = new_env_variable;
		new_env_variable = ft_strjoin(new_env_variable, (*token)->content);
		free(temp);
		*token = (*token)->next;
	}
	temp = ft_cut_str(new_env_variable, 0, find_cara_in_word(new_env_variable,
				'='));
	if (check_if_variable_already_exists(shell, temp) == 1)
		delete_env_variable(shell, temp);
	free(temp);
	add_new_env_variable(new_env_variable, shell);
}

void	add_new_env_variable(char *new_env_variable, t_shell *shell)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (shell->env->index + 2));
	if (new_env == NULL)
		return ;
	i = 0;
	while (shell->env->env[i] != NULL)
	{
		new_env[i] = ft_strdup(shell->env->env[i]);
		i++;
	}
	new_env[i] = new_env_variable;
	i++;
	new_env[i] = NULL;
	free_tab(shell->env->env);
	shell->env->env = new_env;
	shell->env->index++;
	free_tab(shell->env->tab_variable_name);
	free_tab(shell->env->tab_variable_equals);
	create_env_tab(shell);
}

int	check_if_variable_already_exists(t_shell *shell, char *new_env_variable)
{
	int	i;

	i = 0;
	while (shell->env->tab_variable_name[i] != NULL)
	{
		if (ft_strncmp(new_env_variable, shell->env->tab_variable_name[i],
					ft_strlen(shell->env->tab_variable_name[i])) == 0 &&
				ft_strncmp(new_env_variable, shell->env->tab_variable_name[i],
					ft_strlen(shell->env->tab_variable_name[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	export_without_argument(t_shell *shell, t_token *token)
{
	while (token != NULL && token->type == WHITE_SPACE)
		token = token->next;
	if (token == NULL)
	{
		if (shell->env->alpha != NULL)
			free_tab(shell->env->alpha);
		shell->env->alpha = copy_tab(shell->env->env, shell->env->index);
		alpha_sort(shell);
		shell->env->alpha = export_tab(shell->env->alpha);
		print_tab(shell->env->alpha);
		return (1);
	}
	return (0);
}
