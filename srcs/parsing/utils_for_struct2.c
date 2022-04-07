/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_struct2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:07:41 by llescure          #+#    #+#             */
/*   Updated: 2022/04/07 08:07:44 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	delete_token_node(t_token **token)
{
	t_token	*temp;

	temp = (*token)->next;
	(*token)->next = temp->next;
	if ((*token)->next != NULL)
		(*token)->next->previous = temp->previous;
	free(temp->content);
	free(temp);
}

void	delete_last_token_node(t_token **token)
{
	t_token	*temp;

	temp = *token;
	*token = (*token)->previous;
	(*token)->next = NULL;
	free(temp->content);
	free(temp);
}

void	delete_first_token_node(t_token **token)
{
	t_token	*temp;

	temp = *token;
	*token = (*token)->next;
	(*token)->previous = NULL;
	free(temp->content);
	free(temp);
}
