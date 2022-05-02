/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:48:10 by llescure          #+#    #+#             */
/*   Updated: 2022/05/02 14:41:34 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_exit(t_shell *shell, t_token *token, t_command *command)
{
	long long	number;

	g_signal = 0;
	number = 0;
	while (token->next != NULL && token->next->type == WHITE_SPACE)
		token = token->next;
	token = token->next;
	exit_basic_case(shell, token, command);
	if (is_number(token->content) == 1)
		number = ft_atoi_long(token->content);
	if (is_number(token->content) == 0 || number < -2147483648
		|| number > 2147483647)
		exit_numeric_issue(shell, command);
	g_signal = number % 256;
	if (check_number_of_arguments(token, 1, command) == 0)
	{
		if (command->pipe_in == 0 && command->pipe_out == 0)
			ft_putstr_fd("exit\n", 1);
		close_fd(shell, command);
		free_all(shell);
		exit(g_signal);
	}
}

void	exit_basic_case(t_shell *shell, t_token *token, t_command *command)
{
	if (token == NULL || token->type == PIPE)
	{
		if (command->pipe_in == 0 && command->pipe_out == 0)
			ft_putstr_fd("exit\n", 1);
		close_fd(shell, command);
		free_all(shell);
		exit(g_signal);
	}
}

void	exit_numeric_issue(t_shell *shell, t_command *command)
{
	if (command->pipe_in == 0 && command->pipe_out == 0)
		ft_putstr_fd("exit\n", 1);
	error_message(EXIT_ERROR, STDERR_FILENO);
	close_fd(shell, command);
	free_all(shell);
	exit(g_signal);
}

int	check_number_of_arguments(t_token *token, int exit_case, t_command *command)
{
	if (token != NULL && token->type != WHITE_SPACE)
		token = token->next;
	while (token != NULL && token->type == WHITE_SPACE)
		token = token->next;
	if (token != NULL && token->type != PIPE)
	{
		if (exit_case == 1)
		{
			if (command->pipe_in == 0 && command->pipe_out == 0)
				ft_putstr_fd("exit\n", 1);
			error_message(ARGUMENTS, STDERR_FILENO);
			return (g_signal);
		}
		else
		{
			error_message(ARGUMENTS, 1);
			return (-1);
		}
	}
	return (0);
}

void	close_fd(t_shell *shell, t_command *command)
{
	if (shell->fd_pipe_in > 0)
		close(shell->fd_pipe_in);
	if (shell->fd_pipe_out > 0)
		close(shell->fd_pipe_out);
	if (shell->fd_in > 0)
		close(shell->fd_in);
	if (shell->fd_out > 0)
		close(shell->fd_out);
	if (command->pipe_in != 0 || command->pipe_out != 0)
	{
		close(shell->fd[0]);
		close(shell->fd[1]);
	}
}
