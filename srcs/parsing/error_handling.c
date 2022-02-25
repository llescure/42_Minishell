#include "../../include/minishell.h"

void	display_message(char *str, int value_signal, int fd_outfile)
{
	ft_putstr_fd(str, fd_outfile);
	g_signal = value_signal;
}

void	error_message(char *str, int fd_outfile)
{
	if (ft_strncmp(str, "command", ft_strlen("command")) == 0)
		return (display_message("bash: command not found\n", 127, fd_outfile));
	else if (ft_strncmp(str, "syntax", ft_strlen("syntax")) == 0)
		return (display_message("bash: syntax error\n", 2, fd_outfile));
	else if (ft_strncmp(str, "file", ft_strlen("file")) == 0)
		return (display_message("bash: No such file or directory\n", 1,
					fd_outfile));
	else if (ft_strncmp(str, "option", ft_strlen("option")) == 0)
		return (display_message("bash: invalid option\n", 2, fd_outfile));
	else if (ft_strncmp(str, "arguments", ft_strlen("arguments")) == 0)
		return (display_message("bash: too many arguments\n", 1, fd_outfile));
	else if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
		return (display_message("bash: export: not a valid identifier\n", 1,
					fd_outfile));
	else if (ft_strncmp(str, "exit", ft_strlen("exit")) == 0)
		return (display_message("bash: exit: numeric argument required\n", 2,
					fd_outfile));
	else if (ft_strncmp(str, "malloc", ft_strlen("malloc")) == 0)
		return (display_message("Error: couldn't allocate memory\n", -1,
					fd_outfile));
	else if (ft_strncmp(str, "parameters", ft_strlen("parameters")) == 0)
		return (display_message("Error: Too many arguments\n\
Usage: ./minishell\n", -1, fd_outfile));
}

int		error_malloc(t_shell *shell)
{
	error_message("malloc", shell->fd_outfile);
	free_all(shell);
	return (g_signal);
}
