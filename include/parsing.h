/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 07:50:08 by llescure          #+#    #+#             */
/*   Updated: 2022/04/07 07:50:11 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*
** INITIALIZATION
*/

int				init_struct(t_shell *shell, char **envp);
char			*find_word_in_tab(char **env, char *to_find);
char			*delete_until_cara(char *str, int c);
void			set_path(t_shell *shell);

/*
** MAIN FUNCTION TO PARSE
*/

int				parsing(char *user_input, t_shell *shell);
int				clean_input(t_shell *shell);
int				join_clean_input(t_token **token);
void			join_quote_word_expand(t_token **token);
int				look_for_grammar_error(t_token *token, t_shell *shell);
int				look_for_word_in_type(t_token *token, t_type type);
int				check_special_condition_cara(t_type type);

/*
** ENV MANAGEMENT
*/

void			alpha_sort(t_shell *shell);
void			get_env(t_shell *shell, char **envp);
void			create_env_tab(t_shell *shell);
char			**copy_tab(char **tab, int size);
void			get_absolute_path(t_shell *shell, char *path);
void			initialize_env_tab(t_shell *shell);

/*
** SCANNER
*/

int				scanner(char *user_input, t_shell *shell);
int				ft_beginning_lexeme(char *str, int pos, int quote_indication);
int				ft_end_lexeme(char *str, int pos, int quote_indication);
char			*find_lexeme(char *user_input, int beginning, int *end,
					int quote_indication);
char			*ft_cut_str(char *user_input, int beginning, int end);
int				look_for_quote(char *str, int pos, char type_quote,
					int initial_pos);
int				delimit_separator(char *str, int pos, char separator,
					int initial_pos);
int				delimit_expand(char *str, int pos, int initial_pos);
int				delimit_redirections(char *str, int pos, int initial_pos);

/*
** TOKENIZER
*/

int				tokenizer(t_token *token, t_shell *shell);
int				check_content(char *str, t_token **token, t_shell *shell);
void			check_redirection(char *str, t_token **token);
void			check_special_cara(char *str, t_token **token);
int				check_command(char *str, t_shell *shell);

/*
** ERROR MANAGEMENT
*/

void			display_message(char *str, int value_signal, int fd_outfile);
void			error_message(t_error error, int fd_outfile);
int				error_system(t_shell *shell, t_error error);

/*
** QUOTE AND EXPAND MANAGEMENT
*/

void			quote_expansion(t_shell *shell, t_token **token,
					t_type type_expansion);
void			expand_expansion(t_shell *shell, t_token **token);
void			single_quote_expansion(t_shell *shell, t_token **token);
void			double_quote_expansion(t_shell *shell, t_token **token);
char			*remove_cara(char *str, char type_cara_to_delete);
char			*expand_env_variable(char *variable_to_find, t_env *env);
void			expansion_cases(t_shell *shell, char **str);
void			quote_cases(t_shell *shell, char **str, t_type type_expansion);
void			get_identifier(t_shell *shell, char **str);
void			identifier_cases(char **str_to_change, char *original_str,
					char *temp2, t_shell *shell);
char			**split_expand(char *str, char cara);

/*
** COMMAND_MANAGEMENT
*/

int				initialization_command(t_token *token, t_shell *shell);
t_command		*create_command_struct(char *str, t_token *token);
int				append_command_struct(t_command **command, t_token *token,
					t_shell *shell);
void			free_command(t_command **command);
char			*find_correct_path(char **path, char *cmd);
char			*create_command_path(char *cmd);
void			free_tab(char **tab);
void			find_type_command(char *str, t_command **command);

/*
** REDIRECTIONS MANAGEMENT
*/

int				attach_redirections_to_command(t_command *command,
					t_token *token);
void			look_for_redirection_before_command(t_token *token,
					t_redirection **redirection);
void			look_for_redirection_after_command(t_token *token,
					t_redirection **redirection);
t_redirection	*create_redirection_struct(char *str, t_type type);
char			*find_file_for_redir(char	*str, char redir);
int				append_redirection_struct(t_redirection **redirection,
					char *str, t_type type);
void			free_redirection(t_redirection **list);
void			print_redirection(t_redirection *redirection);
void			delete_redirection_in_token(t_token **token);

/*
** PIPE MANAGEMENT
*/

void			define_pipe_input_output(t_command *command, t_token *token);
void			look_for_pipe_before_command(t_command *command,
					t_token *token);
void			look_for_pipe_after_command(t_command *command, t_token *token);

/*
** UTILS_FOR_STRUCT
*/

t_token			*new_token(t_type type, char *content, int id);
void			free_token(t_token **token);
void			add_back_token(t_token **token, t_token *new);
void			print_token(t_token *token);
void			delete_token_node(t_token **token);
void			delete_first_token_node(t_token **token);
void			delete_last_token_node(t_token **token);

#endif
