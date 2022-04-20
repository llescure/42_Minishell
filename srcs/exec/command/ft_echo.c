/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:48:03 by llescure          #+#    #+#             */
/*   Updated: 2022/04/20 14:10:43 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_echo(t_token *token)
{
	int		command_option_active;
	char	*str;

	token = token->next;
	command_option_active = handle_cases_other_than_words(token);
	if (command_option_active < 0)
		return ;
	while (token != NULL && (token->type == WHITE_SPACE
			|| (command_option_active == 1 && token->type
				== COMMAND_OPTION)))
		token = token->next;
	str = ft_strdup("");
	create_buffer_for_echo(token, &str);
	ft_putstr_fd(str, 1);
	if (command_option_active == 0)
		ft_putstr_fd("\n", 1);
	free(str);
}

int	handle_cases_other_than_words(t_token *token)
{
	int	command_option_active;

	command_option_active = 0;
	if (token == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (-1);
	}
	while (token != NULL && ((token->type == COMMAND_OPTION
				&& number_occurence_cara_in_str(token->content, 'n')
				== (int)ft_strlen(token->content) - 1)
			|| (token->type == WHITE_SPACE)))
	{
		if (token->type == COMMAND_OPTION)
			command_option_active = 1;
		token = token->next;
	}
	return (command_option_active);
}

void	create_buffer_for_echo(t_token *token, char **str)
{
	char	*temp;

	while (token != NULL)
	{
		if (token->type == PIPE)
			return ;
		else if (token->type == WHITE_SPACE && (token->next == NULL
				|| token->next->type == PIPE))
			return ;
		else
		{
			temp = *str;
			*str = ft_strjoin(*str, token->content);
			free(temp);
		}
		token = token->next;
	}
}
