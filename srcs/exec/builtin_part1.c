#include "../../include/minishell.h"

void	ft_echo(t_shell *shell)
{
	char	*str;
	char	*temp;
	char	*type;
	int	command_option_active;

	shell->i++;
	if (handle_cases_other_than_words(shell, &command_option_active) != 0)
		return ;
	str = ft_strdup("");
	while (shell->type_bis[shell->i] != NULL)
	{
		type = shell->type_bis[shell->i];
		if (ft_strncmp(type, "pipe", ft_strlen("pipe")) == 0)
			return ;
		else if (ft_strncmp(type, "word", ft_strlen("word")) == 0
			|| ft_strncmp(type, "white_space", ft_strlen("white_space")) == 0
			|| ft_strncmp(type, "single_quote", ft_strlen("single_quote")) == 0
			|| ft_strncmp(type, "double_quote", ft_strlen("double_quote")) == 0
			|| ft_strncmp(type, "expand", ft_strlen("expand")) == 0
			|| ft_strncmp(type, "command", ft_strlen("command")) == 0)
		{
			temp = str;
			str = ft_strjoin(str, shell->token_bis[shell->i]);
			free(temp);
		}
		shell->i++;
	}
	ft_putstr_fd(str, shell->fd_outfile);
	free(str);
	if (command_option_active == 0)
		ft_putstr_fd("\n", shell->fd_outfile);
}

int	handle_cases_other_than_words(t_shell *shell,
		int *command_option_active)
{
	*command_option_active = 0;
	if (shell->token_bis[shell->i] == NULL)
	{
		ft_putstr_fd("\n", shell->fd_outfile);
		return (-1);
	}
	shell->i++;
	while (shell->type_bis[shell->i] != NULL &&
			((ft_strncmp(shell->type_bis[shell->i], "command_option",
						 ft_strlen("command_option")) == 0
			  && number_occurence_cara_in_str(shell->token_bis[shell->i], 'n')
			  == (int)ft_strlen(shell->token_bis[shell->i]) - 1)
			 || (ft_strncmp(shell->token_bis[shell->i], " ",
					 ft_strlen(shell->token_bis[shell->i])) == 0)))
	{
		if (ft_strncmp(shell->type_bis[shell->i], "command_option",
					ft_strlen("command_option")) == 0)
			*command_option_active = 1;
		shell->i++;
	}
	return (0);
}

void ft_pwd(t_shell *shell)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (shell->pwd != NULL)
			free(shell->pwd);
		shell->pwd = ft_strdup(cwd);
		ft_putstr_fd(shell->pwd, shell->fd_outfile);
		ft_putstr_fd("\n", shell->fd_outfile);
	}
}

void	ft_cd(t_shell *shell)
{
	shell->i++;
	while (shell->token_bis[shell->i] != NULL &&
			ft_strncmp(shell->type_bis[shell->i], "white_space",
				ft_strlen("white_space")) == 0)
		shell->i++;
	if (shell->token_bis[shell->i] == NULL)
	{
		chdir(shell->absolute_path);
		return ;
	}
	if (chdir(shell->token_bis[shell->i]) == -1)
	{
		error_message("file", shell->fd_outfile);
		return ;
	}
}
