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
		if (look_for_type_after_command(*token, PIPE) == 0
				&& look_for_type_before_command(*token, PIPE) == 0)
			ft_putstr_fd("exit\n", 1);
		error_message(EXIT_ERROR, 1);
		if (look_for_type_after_command(*token, PIPE) == 1
				|| look_for_type_before_command(*token, PIPE) == 1)
				return ;
		free_all(shell);
		exit(g_signal);
	}
	*token = (*token)->next;
	if (check_number_of_arguments(*token) != 0)
		return ;
	if (look_for_type_after_command(*token, PIPE) == 0
			&& look_for_type_before_command(*token, PIPE) == 0)
		ft_putstr_fd("exit\n", 1);
	if (look_for_type_after_command(*token, PIPE) == 1
			|| look_for_type_before_command(*token, PIPE) == 1)
			return ;
	free_all(shell);
	exit(g_signal % 256);
}

void	exit_basic_case(t_shell *shell, t_token *token)
{
	if (token == NULL && look_for_type_before_command(token, PIPE) == 0)
	{
		printf("type_before = %d\n", look_for_type_before_command(token, PIPE));
		ft_putstr_fd("exit\n", 1);
		free_all(shell);
		exit (g_signal);
	}
}

int	check_number_of_arguments(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == WHITE_SPACE)
		{
			if (look_for_type_after_command(token, PIPE) == 0
				&& look_for_type_before_command(token, PIPE) == 0)
				ft_putstr_fd("exit\n", 1);
			error_message(ARGUMENTS, 1);
			return (g_signal);
		}
		token = token->next;
	}
	return (0);
}
