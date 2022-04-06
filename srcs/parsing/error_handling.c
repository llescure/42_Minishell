#include "../../include/minishell.h"

void	display_message(char *str, int value_signal, int fd_outfile)
{
	ft_putstr_fd(str, fd_outfile);
	g_signal = value_signal;
}

void	error_message(t_error str, int fd_outfile)
{
	if (str == COMMAND_ERROR)
		return (display_message("bash: command not found\n", 127, fd_outfile));
	else if (str == SYNTAX)
		return (display_message("bash: syntax error\n", 2, fd_outfile));
	else if (str == FILES)
		return (display_message("bash: No such file or directory\n", 1,
					fd_outfile));
	else if (str == OPTION)
		return (display_message("bash: invalid option\n", 2, fd_outfile));
	else if (str == ARGUMENTS)
		return (display_message("bash: too many arguments\n", 1, fd_outfile));
	else if (str == EXPORT_ERROR)
		return (display_message("bash: export: not a valid identifier\n", 1,
					fd_outfile));
	else if (str == EXIT_ERROR)
		return (display_message("bash: exit: numeric argument required\n", 2,
					fd_outfile));
	else if (str == MALLOC)
		return (display_message("Error: couldn't allocate memory\n", -1,
					fd_outfile));
	else if (str == PIPE_FORK)
		return (display_message("Error: couldn't fork or pipe\n", -1,
					fd_outfile));
	else if (str == PARAMETERS)
		return (display_message("Error: Too many arguments\n\
Usage: ./minishell\n", -1, fd_outfile));
}

int		error_system(t_shell *shell, t_error str)
{
	error_message(str, shell->fd_outfile);
	free_all(shell);
	return (g_signal);
}
