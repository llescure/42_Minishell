#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include "../srcs/libft/include/libft.h"

typedef struct s_env {
    char		**env;
    char		**alpha;
    int			index;
}               t_env;

typedef struct s_shell {
  char			*cmd;
  char			option;
  char			*str;
  char			*pwd;
  char			*absolute_path;
  t_env			*env;
  t_list		*variables;
}               t_shell;

int		g_signal;

void	handle_builtin(t_shell *shell);
void	ft_pwd(t_shell *shell);
int		ft_echo(char *str, char option);
void	init_struct(t_shell *shell, char **envp);
int		ft_error(t_shell *shell);
int		ft_cd(t_shell *shell);
void	get_absolute_path(t_shell *shell, char *path);
void	quit_program(t_shell *shell);
int		ft_export(t_shell *shell);
void	alpha_sort(t_shell *shell);
void	get_env(t_shell *shell, char **envp);
void	create_variable(t_shell *shell);
void	print_env(t_shell *shell, char **envp);
void	launch_shell(t_shell *shell);
void	free_all(t_shell *shell);
void	create_new_line(int signum);

#endif
