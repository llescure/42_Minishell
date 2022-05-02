# 42_Minishell

### Project ###
Reproduce some behaviors of bash --posix :
- Pipe
- Redirections >, >>, <, <<
- Builtin : echo with -n option, ls, pwd, unset, export, env, cd
- Quote and double quote management

### Parsing advice ###
* Use enum for clarity for your token types
`
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
`

* Use a double linked list to keep your token
`
typedef struct s_token
{
	t_type			type;
	char			*content;
	int				id;
	struct s_token	*next;
	struct s_token	*previous;
}				t_token;
`

* Delete redirection, quote and double quote once you have expanded them

### Test ###
Some tests I have made: https://docs.google.com/spreadsheets/d/1ZxZ9KYoeZQ0OrbIXnSyWBm3jtcfImfA1utGPofo0-4E/edit#gid=1047301068
