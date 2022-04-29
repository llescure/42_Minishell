/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:49:06 by llescure          #+#    #+#             */
/*   Updated: 2022/04/29 20:36:23 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 2;
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		g_signal = 0;
	}
}

void	handle_exec_signals(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", 1);
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 1);
}
