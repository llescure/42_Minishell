#include "../../include/minishell.h"

void	ft_exit(t_shell *shell, t_token **token)
{
	*token = (*token)->next;
	exit_basic_case(shell, *token);
	while (*token != NULL && (*token)->type == WHITE_SPACE)
		*token = (*token)->next;
	exit_basic_case(shell, *token);
	if (is_number((*token)->content) == 1)
		g_signal = ft_atoi((*token)->content);
	else if (is_number((*token)->content) == 0)
	{
		ft_putstr_fd("exit\n", 1);
		error_message(EXIT_ERROR, 1);
		free_all(shell);
		exit(g_signal);
	}
	*token = (*token)->next;
	if (check_number_of_arguments(shell, *token) != 0)
		exit(g_signal);
	free_all(shell);
	ft_putstr_fd("exit\n", 1);
	exit(g_signal % 256);
}

void	exit_basic_case(t_shell *shell, t_token *token)
{
	if (token == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		free_all(shell);
		exit (g_signal);
	}
}

int	check_number_of_arguments(t_shell *shell, t_token *token)
{
	while (token != NULL)
	{
		if (token->type == WHITE_SPACE)
		{
			ft_putstr_fd("exit\n", 1);
			error_message(ARGUMENTS, 1);
			free_all(shell);
			return (g_signal);
		}
		token = token->next;
	}
	return (0);
}
