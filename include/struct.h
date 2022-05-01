/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 07:49:58 by llescure          #+#    #+#             */
/*   Updated: 2022/05/01 17:52:21 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*
** Definition of main structure token which will store the type, content and id
** of the token
*/

typedef enum e_type
{
	WORD=0,
	COMMAND,
	COMMAND_OPTION,
	WHITE_SPACE,
	QUOTE,
	D_QUOTE,
	EQUAL,
	ERROR,
	PIPE,
	EXPAND,
	REDIR_RIGHT,
	REDIR_LEFT,
	D_REDIR_RIGHT,
	HEREDOC,
	EMPTY
}				t_type;

typedef struct s_token
{
	t_type			type;
	char			*content;
	int				id;
	struct s_token	*next;
	struct s_token	*previous;
}				t_token;

/*
** Definition of structure for env variable
*/

typedef struct s_env {
	char			**env;
	char			**alpha;
	char			**tab_variable_name;
	char			**tab_variable_equals;
	int				index;
}				t_env;

/*
** Definition of structure in case of error
*/

typedef enum e_error
{
	COMMAND_ERROR,
	SYNTAX,
	FILES,
	OPTION,
	ARGUMENTS,
	EXPORT_ERROR,
	EXIT_ERROR,
	MALLOC,
	PIPE_FORK,
	PARAMETERS
}				t_error;

/*
** Definition of structure command that will store if the command needs to be
** piped or if the input fd or output fd needs to be changed due to redirection
*/

typedef struct s_redirection
{
	char					*file;
	t_type					type;
	struct s_redirection	*next;
}				t_redirection;

typedef enum e_command_type
{
	EXIT,
	ECHO_CMD,
	CD,
	PWD,
	EXPORT,
	UNSET,
	BINARY,
	EXECUTABLE,
	VOID,
	ENV
}				t_command_type;

typedef struct s_command
{
	t_command_type		command_type;
	t_redirection		*redirection;
	int					pipe_in;
	int					pipe_out;
	int					id;
	struct s_command	*next;
}					t_command;

/*
** Main structure with all information
*/

typedef struct s_shell
{
	char				*pwd;
	char				**path;
	char				*absolute_path;
	int					fd_in;
	int					fd_out;
	int					fd_pipe_in;
	int					fd_pipe_out;
	int					save_infile;
	int					save_outfile;
	t_env				*env;
	t_token				*token;
	t_command			*command;
	int					shlvl;
	int					fd[2];
}				t_shell;

#endif
