#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_env {
    char		**env;
    char		**alpha;
	char		**tab_variable_name;
	char		**tab_variable_equals;
    int			index;
}               t_env;

typedef enum	e_error
{
	COMMAND_ERROR,
	SYNTAX,
	FILES,
	OPTION,
	ARGUMENTS,
	EXPORT_ERROR,
	EXIT_ERROR,
	MALLOC,
	PARAMETERS
}				t_error;

typedef struct	s_redirection
{
	char					*file;
	t_category				category;
	struct s_redirection	*next;
}				t_redirection;

typedef enum	e_command_type
{
	EXIT,
	ECHO_CMD,
	CD,
	PWD,
	EXPORT,
	UNSET,
	BINARY,
	ENV
}				t_command_type;

typedef	struct		s_command
{
	t_command_type		command_type;
	t_redirection		*redirection;
	int					pipe_input;
	int					pipe_output;
	int					id;
	struct s_command	*next;
}					t_command;

typedef struct s_shell
{
  char				*pwd;
  char				**path;
  char				*absolute_path;
  int				fd_infile;
  int				fd_outfile;
  t_env				*env;
  t_double_list		*token;
  t_type			*type;
  t_command			*command;
  int				command_count;
}               	t_shell;

#endif
