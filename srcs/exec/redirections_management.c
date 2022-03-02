#include "../../include/minishell.h"

int		open_infile_redirection(t_shell *shell)
{
	char	*type;
	char	*next_token;

	type = shell->type_bis[shell->i];
	shell->i++;
	while (shell->token_bis[shell->i] != NULL
	&& ft_strncmp(shell->type_bis[shell->i], "word",
			ft_strlen("word")) != 0
	&& ft_strncmp(shell->type_bis[shell->i], "command",
			ft_strlen("command")) != 0)
		shell->i++;
	if (shell->token_bis[shell->i] == NULL)
	{
		error_message("syntax", shell->fd_outfile);
		return (g_signal);
	}
	next_token = shell->token_bis[shell->i];
	if (ft_strncmp(type, "redir_left", ft_strlen(type)) == 0)
	{
		shell->fd_infile = open(next_token, O_RDONLY);
		dup2(shell->fd_infile, 0);
	}
	if (shell->fd_infile < 0)
	{
		error_message("file", 1);
		return (g_signal);
	}
	return (0);
}

int		open_outfile_redirection(t_shell *shell)
{
	char	*type;
	char	*next_token;

	type = shell->type_bis[shell->i];
	shell->i++;
	while (shell->token_bis[shell->i] != NULL
	&& ft_strncmp(shell->type_bis[shell->i], "word",
			ft_strlen("word")) != 0
	&& ft_strncmp(shell->type_bis[shell->i], "command",
			ft_strlen("command")) != 0)
		shell->i++;
	if (shell->token_bis[shell->i] == NULL)
	{
		error_message("syntax", shell->fd_outfile);
		return (g_signal);
	}
	next_token = shell->token_bis[shell->i];
	if (ft_strncmp(type, "redir_right", ft_strlen(type)) == 0)
	{
		shell->fd_outfile = open(next_token,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(shell->fd_outfile, 1);
	}
	else if (ft_strncmp(type, "d_redir_right", ft_strlen(type)) == 0)
	{
		shell->fd_outfile = open(next_token,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
		dup2(shell->fd_outfile, 1);
	}
	if (shell->fd_infile < 0 || shell->fd_outfile < 0)
	{
		error_message("file", shell->fd_outfile);
		return (g_signal);
	}
	return (0);
}
