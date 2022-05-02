/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:12:42 by llescure          #+#    #+#             */
/*   Updated: 2022/05/02 14:39:12 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_cd(t_shell *shell, t_token *token, t_command *command)
{
	int	return_value;

	token = token->next;
	while (token != NULL && token->type == WHITE_SPACE)
		token = token->next;
	if (token == NULL)
	{
		chdir(shell->absolute_path);
		g_signal = 0;
		return ;
	}
	if (token->next != NULL)
		token = token->next;
	if (check_number_of_arguments(token, 0, command) < 0)
		return ;
	return_value = chdir(token->content);
	if (return_value == -1)
		error_message(FILES, 1);
}
