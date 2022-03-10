#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "../srcs/libft/include/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <errno.h>
# include "struct.h"
# include "parsing.h"
# include "exec.h"

/*
 ** GLOBAL VARIABLE
*/

int		g_signal;

#endif
