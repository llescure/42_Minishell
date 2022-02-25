#include "../../include/minishell.h"

int		open_file_redirection(t_shell *shell)
{
	char	*type;
	char	*next_token;

	type = shell->type_bis[shell->i];
	next_token = shell->token_bis[shell->i + 1];
	if (ft_strncmp(type, "redir_left", ft_strlen(type)) == 0)
		shell->fd_infile = open(next_token, O_RDONLY);
	else if (ft_strncmp(type, "redir_right", ft_strlen(type)) == 0)
		shell->fd_outfile = open(next_token,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (ft_strncmp(type, "d_redir_right", ft_strlen(type)) == 0)
		shell->fd_outfile = open(next_token,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (shell->fd_infile < 0 || shell->fd_outfile < 0)
	{
		error_message("file", shell->fd_outfile);
		return (g_signal);
	}
	return (0);
}
