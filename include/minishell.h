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
	char		**tab_variable_name;
	char		**tab_variable_equals;
    int			index;
}               t_env;

typedef struct s_shell {
  char				*str;
  char				*pwd;
  char				**path;
  char				*absolute_path;
  char				*cmd;
  t_env				*env;
  t_double_list		*token;
  t_double_list		*type;
}               	t_shell;

int		g_signal;

/*
 ** EXEC FUNCTIONS
*/

void	handle_builtin(t_shell *shell);
void	ft_pwd(t_shell *shell);
int		ft_echo(char *str, char option);
int		ft_cd(t_shell *shell);
void	quit_program(t_shell *shell);
int		ft_export(t_shell *shell);
int		launch_shell(t_shell *shell);
void	free_all(t_shell *shell);
void	handle_signals(int signum);
void	handle_exec_signals(int signum);
int		prompt(char **user_input, t_shell *shell);

/*
 ** PARSING FUNCTIONS
*/

int		init_struct(t_shell *shell, char **envp);
void	print_tab(char **tab);
void	alpha_sort(t_shell *shell);
void	get_env(t_env *shell, char **envp);
void	create_env_tab(t_env *env);
void	get_absolute_path(t_shell *shell, char *path);
void	create_variable(t_shell *shell);
int		parsing(char *user_input, t_shell *shell);
char	*find_word_in_tab(char **env, char *to_find);
char	*find_correct_path(char **path, char *cmd);
char	*create_command_path(char *cmd);
char	*delete_until_cara(char *str, int c);
void	free_tab(char **tab);
int		scanner(char *user_input, t_shell *shell);
int		ft_beginning_lexeme(char *str, int pos, int quote_indication);
int		ft_end_lexeme(char *str, int pos, int quote_indication);
char	*find_lexeme(char *user_input, int beginning, int *end,
		int quote_indication);
char	*ft_cut_str(char *user_input, int beginning, int end);
int		look_for_quote(char *str, int pos, char type_quote, int initial_pos);
void	display_message(char *str, int value_signal);
void	error_message(char *str);
int		delimit_separator(char *str, int pos, char separator, int initial_pos);
int		delimit_expand(char *str, int pos, int initial_pos);
int		tokenizer(t_double_list *token, t_shell *shell);
int		check_first_content(char *str, t_double_list **list, t_shell *shell);
int		check_content(char *str, t_double_list **list, t_shell *shell);
void	check_redirection(char *str, t_double_list **list);
void	check_first_redirection(char *str, t_double_list **list);
void	check_first_special_cara(char *str, t_double_list **list);
void	check_special_cara(char *str, t_double_list **list);
int		check_command(char *str, t_shell *shell);
int		look_for_word_in_type(t_double_list *list, char *str);
void	look_for_grammar_error(t_double_list *list, t_double_list *type,
		t_shell *shell);
void	quote_expansion(t_shell *shell, t_double_list *type,
		t_double_list **list, char type_cara_to_delete, char *type_expansion);
void	expand_expansion(t_shell *shell, t_double_list *type,
		t_double_list **list);
void	single_quote_expansion(t_shell *shell, t_double_list *type,
		t_double_list **list);
void	double_quote_expansion(t_shell *shell, t_double_list *type,
		t_double_list **list);
char	*remove_cara(char *str, char type_cara_to_delete);
char	*expand_env_variable(char *variable_to_find, t_env *env);
void	expansion_cases(t_shell *shell, void **str);
void	quote_cases(t_shell *shell, char **str, char type_cara_to_delete);
void	get_identifier(t_shell *shell, char **str);
void	identifier_cases(char **str_to_change, char *original_str, char *temp2,
		t_shell *shell);
char	**split_expand(char *str, char cara);
int		clean_input(t_shell *shell);
int		join_clean_input(t_double_list **list, t_double_list *type);

#endif
