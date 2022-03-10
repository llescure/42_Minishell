#ifndef EXEC_H
# define EXEC_H

/*
** LAUNCH_SHELL
*/

int			launch_shell(t_shell *shell);
int			prompt(char **user_input, t_shell *shell);
void		free_all(t_shell *shell);

/*
** EXECUTE_INPUT
*/

int			execute_input(t_shell *shell, t_type *type, t_double_list *token,
		t_command *command);
void		handle_builtin(t_shell *shell, t_type *type, t_double_list *token,
			t_command *command);
void		execute_child_process(t_shell *shell, t_type *type,
			t_double_list *token, t_command *command);

/*
** REDIRECTIONS
*/

int			open_infile_redirection(t_shell *shell);
int			open_outfile_redirection(t_shell *shell);

/*
** COMMAND
*/

void		ft_pwd(t_shell *shell);
void		ft_echo(t_shell *shell);
void		ft_exit(t_shell *shell);
int			handle_cases_other_than_words(t_shell *shell,
			int *command_option_active);
void		ft_cd(t_shell *shell);
void		ft_export(t_shell *shell);
int			export_without_argument(t_shell *shell);
char		**create_binary(t_shell *shell);
int			command_lenght(t_shell *shell, int index);
void		exit_basic_case(t_shell *shell);
int			check_number_of_arguments(t_shell *shell);
int			check_if_variable_already_exists(t_shell *shell,
		char *new_env_variable);
void		delete_env_variable(t_shell *shell, char *env_to_delete);
void		ft_unset(t_shell *shell);
void		execute_binary(t_shell *shell);
void		create_new_env_variable(t_shell *shell);
void		create_lonely_env_variable(t_shell *shell);
void		add_new_env_variable(char *new_env_variable, t_shell *shell);

/*
** SIGNALS
*/

void		handle_signals(int signum);
void		handle_exec_signals(int signum);

#endif