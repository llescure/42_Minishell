/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:56:05 by llescure          #+#    #+#             */
/*   Updated: 2022/04/08 16:57:03 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	command_is_builtin(char *str)
{
	if (double_ft_strncmp(str, "exit") == 1
		|| double_ft_strncmp(str, "pwd") == 1
		|| double_ft_strncmp(str, "cd") == 1
		|| double_ft_strncmp(str, "export") == 1
		|| double_ft_strncmp(str, "unset") == 1
		|| ft_strncmp(str, "./", ft_strlen("./")) == 0
		|| double_ft_strncmp(str, "env") == 1
		|| double_ft_strncmp(str, "echo") == 1)
		return (1);
	return (0);
}
