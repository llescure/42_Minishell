/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:28:55 by llescure          #+#    #+#             */
/*   Updated: 2022/02/11 15:45:47 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_join_tab(char **tab)
{
	int	i;
	char	*temp;
	char	*new_str;

	i = 1;
	new_str = "";
	new_str = ft_strjoin(new_str, tab[0]);
	while (tab[i] != NULL)
	{
		temp = new_str;
		new_str = ft_strjoin(new_str, tab[i]);
		free(temp);
		i++;
	}
	return (new_str);
}
