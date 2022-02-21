#include "../../include/minishell.h"

int		open_file_redirection(t_double_list *type, t_double_list *token,
	   	int *fd_infile, int *fd_outfile)
{
	if (ft_strncmp(type->content, "redir_left",
				ft_strlen(type->content)) == 0)
		*fd_infile = open(token->next->content, O_RDONLY);
	else if (ft_strncmp(type->content, "redir_right",
				ft_strlen(type->content)) == 0)
		*fd_outfile = open(token->next->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (ft_strncmp(token->content, "d_redir_right",
				ft_strlen(token->content)) == 0)
		*fd_outfile = open(token->next->content,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (*fd_infile < 0 || *fd_outfile < 0)
	{
		error_message("file");
		return (g_signal);
	}
	return (0);
}
