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
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <errno.h>

# define INTERACTIVE_MODE 1
# define NORMAL_MODE 0

typedef struct s_env {
    char		**env;
    char		**alpha;
    int			index;
}               t_env;

typedef struct s_shell {
  char				*str;
  char				*pwd;
  char				**path;
  char				*absolute_path;
  char				*cmd;
  t_env				*env;
  t_list			*token;
  t_double_list		*type;
}               	t_shell;

/*typedef enum e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}			t_builtins; */

int		g_signal;

void	handle_builtin(t_shell *shell);
void	ft_pwd(t_shell *shell);
int		ft_echo(char *str, char option);
int		init_struct(t_shell *shell, char **envp);
int		ft_cd(t_shell *shell);
void	get_absolute_path(t_shell *shell, char *path);
void	quit_program(t_shell *shell);
int		ft_export(t_shell *shell);
void	alpha_sort(t_shell *shell);
void	get_env(t_env *shell, char **envp);
void	create_variable(t_shell *shell);
void	print_env(t_shell *shell);
int		launch_shell(t_shell *shell);
void	free_all(t_shell *shell);
void	handle_signals(int signum);
void	handle_exec_signals(int signum);
int		prompt(char **user_input, t_shell *shell);
int		parsing(char *user_input, t_shell *shell);
char	*find_word_in_tab(char **env, char *to_find);
char	*find_correct_path(char **path, char *cmd);
char	*create_command_path(char *cmd);
char	*delete_until_cara(char *str, int c);
void	free_tab(char **tab);
int		scanner(char *user_input, t_shell *shell);
int		ft_beginning_lexeme(char *str, int pos, int *found_quote);
int		ft_end_lexeme(char *str, int pos, int found_quote);
char	*find_lexeme(char *user_input, int beginning, int *end);
char	*ft_cut_str(char *user_input, int beginning, int end);
int		look_for_quote(char *str, int pos, char type_quote);
void	display_message(char *str, int value_signal);
void	error_message(char *str);
int		delimit_separator(char *str, int pos, char separator, int initial_pos);
int		delimit_expand(char *str, int pos);
int		tokenizer(t_list *token, t_shell *shell);
int		check_first_content(char *str, t_double_list **list, t_shell *shell);
int		check_content(char *str, t_double_list **list, t_shell *shell);
void	check_redirection(char *str, t_double_list **list);
void	check_first_redirection(char *str, t_double_list **list);
int		check_command(char *str, t_shell *shell);
int		look_for_error_in_type(t_double_list *list);

#endif
