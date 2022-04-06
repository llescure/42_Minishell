/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_occurence_cara_in_str.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:35:19 by llescure          #+#    #+#             */
/*   Updated: 2022/04/06 14:54:50 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	number_occurence_cara_in_str(char *str, char c)
{
	int	compt;
	int	i;

	compt = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			compt++;
		i++;
	}
	return (compt);
}
