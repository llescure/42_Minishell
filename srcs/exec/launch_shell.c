#include "../../include/minishell.h"

int prompt(char **user_input, t_shell *shell)
{
	char	*lign;

	lign = *user_input;
	if (lign != NULL)
	{
		free(lign);
		ft_free_list(&shell->token);
		lign = NULL;
	}
	lign = readline("my_minishell# ");
	if (lign != NULL)
		add_history(lign);
	else
	{
		ft_free_list(&shell->token);
		free_all(shell);
		ft_putstr_fd("exit\n", 1);
		return (-1);
	}
	*user_input = lign;
	return (0);
}

void	launch_shell(t_shell *shell)
{
	char	*user_input;

	user_input = NULL;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	while (1)
	{
		if (prompt(&user_input, shell) < 0)
			return ;
		parsing(user_input, shell);
	}
}
