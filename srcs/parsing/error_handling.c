#include "../../include/minishell.h"

void	display_message(char *str, int value_signal)
{
	ft_putstr_fd(str, 1);
	g_signal = value_signal;
}

void	error_message(char *str)
{
	if (ft_strncmp(str, "command", ft_strlen("command")) == 0)
		return (display_message("bash: command not found\n", 127));
	else if (ft_strncmp(str, "command_option", ft_strlen("command_option")) == 0)
		return (display_message("bash: command option not available\n", 127));
	else if (ft_strncmp(str, "syntax", ft_strlen("syntax")) == 0)
		return (display_message("bash: syntax error\n", 2));
	else if (ft_strncmp(str, "file", ft_strlen("file")) == 0)
		return (display_message("bash: No such file or directory\n", 1));
	else if (ft_strncmp(str, "option", ft_strlen("option")) == 0)
		return (display_message("bash: invalid option\n", 2));
	else if (ft_strncmp(str, "arguments", ft_strlen("arguments")) == 0)
		return (display_message("bash: too many arguments\n", 1));
	else if (ft_strncmp(str, "exit", ft_strlen("exit")) == 0)
		return (display_message("bash: exit: numeric argument required\n", 2));
	else if (ft_strncmp(str, "malloc", ft_strlen("malloc")) == 0)
		return (display_message("Error: couldn't allocate memory\n", -1));
	else if (ft_strncmp(str, "parameters", ft_strlen("parameters")) == 0)
		return (display_message("Error: Too many arguments\n\
Usage: ./minishell\n", -1));
}
