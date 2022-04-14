#include "../../include/minishell.h"

void	ft_exit(t_shell *shell, t_token *token)
{
	long long	number;

	number = 0;
	while (token->next != NULL && token->next->type == WHITE_SPACE)
		token = token->next;
	token = token->next;
	exit_basic_case(shell, token);
	if (is_number(token->content) == 1)
		number = ft_atoi_long(token->content);
	if (is_number(token->content) == 0 || number < -2147483648
			|| number > 2147483647)
	{
		ft_putstr_fd("exit\n", 1);
		error_message(EXIT_ERROR, 1);
		free_all(shell);
		exit(g_signal);
	}
	g_signal = number % 256;
	if (check_number_of_arguments(token) != 0)
	{
		ft_putstr_fd("exit\n", 1);
		free_all(shell);
		exit(g_signal);
	}
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

int	check_number_of_arguments(t_token *token)
{
	if (token != NULL && token->type != WHITE_SPACE)
		token = token->next;
	while (token != NULL && token->type == WHITE_SPACE)
		token = token->next;
	if (token != NULL)
	{
		ft_putstr_fd("exit\n", 1);
		error_message(ARGUMENTS, 1);
		return (g_signal);
	}
	return (0);
}
