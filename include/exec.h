/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 07:49:46 by llescure          #+#    #+#             */
/*   Updated: 2022/04/08 15:44:59 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int			execute_input(t_shell *shell, t_token *token, t_command *command);
void		handle_builtin(t_shell *shell, t_token **token, t_command *command);
void		execute_child_process(t_shell *shell, t_token *token,
				t_command *command);
void		execute_parent_process(t_shell *shell, t_token **token,
				t_command *command, int pid);

/*
** REDIRECTIONS
*/

int			handle_redirection(t_redirection *redirection, t_shell *shell);
int			open_file_descriptor(int in, int out, t_shell *shell);
int			handle_heredoc(char *file, t_shell *shell);
void		new_line_until_delimitator(int *fd, char *file);

/*
** COMMAND
*/

void		ft_pwd(t_shell *shell);
void		ft_echo(t_token **token);
void		create_buffer_for_echo(t_token **token, int command_option_active,
				char **str);
void		ft_exit(t_shell *shell, t_token **token);
int			handle_cases_other_than_words(t_token *token);
void		ft_cd(t_shell *shell, t_token **token);
void		ft_export(t_shell *shell, t_token **token);
int			condition_for_token_export(t_type type);
int			export_without_argument(t_shell *shell, t_token *token);
char		**create_binary(t_token *token);
int			command_lenght(t_token *token);
void		exit_basic_case(t_shell *shell, t_token *token);
int			check_number_of_arguments(t_token *token);
int			check_if_variable_already_exists(t_shell *shell,
				char *new_env_variable);
void		delete_env_variable(t_shell *shell, char *env_to_delete);
void		ft_unset(t_shell *shell, t_token **token);
char		**copy_previous_env_variable(t_shell *shell, char *env_to_delete);
void		execute_binary(t_shell *shell, t_token *token);
void		create_new_env_variable(t_shell *shell, t_token **token);
void		create_lonely_env_variable(t_shell *shell, t_token *token);
void		add_new_env_variable(char *new_env_variable, t_shell *shell);
void		execute_executable(t_shell *shell, t_token *token);
void		print_env(char **tab);
void		print_tab(char **tab);
char		**export_tab(char **tab);

/*
** SIGNALS
*/

void		handle_signals(int signum);
void		handle_exec_signals(int signum);

#endif
