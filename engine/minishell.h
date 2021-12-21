#ifndef MINISHELL_H
# define MINISHELL_H

#include <termcap.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <libc.h>
#include <limits.h>
#include "../42_libft/include/libft.h"

typedef struct s_shell {
  char *cmd;
  char option;
  char *str;
  char *pwd;
  char *cd_option;
  char *absolute_path;
  char **env;
}               t_shell;

void ft_pwd(t_shell *shell);
int	ft_echo(char *str, char option);
void init_struct(t_shell *shell);
void ft_error(t_shell *shell);
int ft_cd(t_shell *shell);
int get_absolute_path(t_shell *shell);
void quit_program(t_shell *shell);
int ft_export(t_shell *shell, char **envp);
void alpha_sort(t_shell *shell, int index);

#endif
