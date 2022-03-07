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
  char				*pwd;
  char				**path;
  char				*absolute_path;
  int				fd_infile;
  int				fd_outfile;
  t_env				*env;
  t_double_list		*token;
  t_type			*type;
  int				command_count;
}               	t_shell;

typedef enum	e_error
{
	COMMAND_ERROR,
	SYNTAX,
	FILES,
	OPTION,
	ARGUMENTS,
	EXPORT,
	EXIT,
	MALLOC,
	PARAMETERS
}				t_error;

int		g_signal;

/*
 ** EXEC FUNCTIONS
*/

void	handle_builtin(t_shell *shell, char *str);
void	ft_pwd(t_shell *shell);
void	ft_echo(t_shell *shell);
void	ft_exit(t_shell *shell);
int		handle_cases_other_than_words(t_shell *shell,
		int *command_option_active);
void	ft_cd(t_shell *shell);
void	ft_export(t_shell *shell);
int		export_without_argument(t_shell *shell);
void	create_new_env_variable(t_shell *shell);
void	create_lonely_env_variable(t_shell *shell);
void	add_new_env_variable(char *new_env_variable, t_shell *shell);
char	**create_binary(t_shell *shell);
int		command_lenght(t_shell *shell, int index);
int		launch_shell(t_shell *shell);
void	free_all(t_shell *shell);
void	handle_signals(int signum);
void	handle_exec_signals(int signum);
int		prompt(char **user_input, t_shell *shell);
int		execute_input(t_shell *shell, char *user_input,
		t_type *type, t_double_list *token);
int		open_infile_redirection(t_shell *shell);
int		open_outfile_redirection(t_shell *shell);
void	exit_basic_case(t_shell *shell);
int		check_number_of_arguments(t_shell *shell);
int		check_if_variable_already_exists(t_shell *shell, char *new_env_variable);
void	delete_env_variable(t_shell *shell, char *env_to_delete);
void	ft_unset(t_shell *shell);
void	execute_binary(t_shell *shell);
void	execute_child_process(t_shell *shell, char *str);

/*
 ** PARSING FUNCTIONS
*/

int		init_struct(t_shell *shell, char **envp);
void	print_tab(char **tab);
void	alpha_sort(t_shell *shell);
void	get_env(t_shell *shell, char **envp);
char	**export_tab(char **tab);
void	create_env_tab(t_shell *shell);
char	**copy_tab(char **tab, int size);
void	get_absolute_path(t_shell *shell, char *path);
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
void	display_message(char *str, int value_signal, int fd_outfile);
void	error_message(t_error error, int fd_outfile);
int		error_malloc(t_shell *shell);
int		delimit_separator(char *str, int pos, char separator, int initial_pos);
int		delimit_expand(char *str, int pos, int initial_pos);
int		tokenizer(t_double_list *type, t_shell *shell);
int		check_first_content(char *str, t_type **type, t_shell *shell);
int		check_content(char *str, t_type **type, t_shell *shell);
void	check_redirection(char *str, t_type **type);
void	check_first_redirection(char *str, t_type **type);
void	check_first_special_cara(char *str, t_type **type);
void	check_special_cara(char *str, t_type **type);
int		check_command(char *str, t_shell *shell);
int		look_for_word_in_type(t_type *type, t_category category);
void	look_for_grammar_error(t_type *type, int fd_outfile,
		t_shell *shell);
void	quote_expansion(t_shell *shell, t_type *type,
		t_double_list **token, t_category category_expansion);
void	expand_expansion(t_shell *shell, t_type *type,
		t_double_list **token);
void	single_quote_expansion(t_shell *shell, t_type *type,
		t_double_list **token);
void	double_quote_expansion(t_shell *shell, t_type *type,
		t_double_list **token);
char	*remove_cara(char *str, char type_cara_to_delete);
char	*expand_env_variable(char *variable_to_find, t_env *env);
void	expansion_cases(t_shell *shell, void **str);
void	quote_cases(t_shell *shell, char **str, t_category category_expansion);
void	get_identifier(t_shell *shell, char **str);
void	identifier_cases(char **str_to_change, char *original_str, char *temp2,
		t_shell *shell);
char	**split_expand(char *str, char cara);
int		check_and_expand_input(t_shell *shell);
int		join_clean_input(t_double_list **token, t_type *type);
int		special_condition_cara_is_respected(t_category category);
void	set_path(t_shell *shell);

#endif
