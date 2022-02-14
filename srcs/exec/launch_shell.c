#include "../../include/minishell.h"

int prompt(char **user_input, t_shell *shell)
{
	char	*lign;

	lign = *user_input;
	if (lign != NULL)
	{
		if (lign[0] != '\0')
		{
			ft_double_free_list(&shell->token, 1);
			ft_double_free_list(&shell->type, 0);
		}
		free(lign);
		lign = NULL;
	}
	lign = readline("my_minishell# ");
	if (lign != NULL)
		add_history(lign);
	else
	{
		if (shell->token != NULL)
		{
			ft_double_free_list(&shell->token, 1);
			ft_double_free_list(&shell->type, 0);
		}
		free_all(shell);
		ft_putstr_fd("exit\n", 1);
		return (-1);
	}
	*user_input = lign;
	return (0);
}

int	launch_shell(t_shell *shell)
{
	char	*user_input;

	user_input = NULL;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	while (1)
	{
		if (prompt(&user_input, shell) != 0)
			return (g_signal);
		if (parsing(user_input, shell) != 0)
			return (g_signal);
	}
}
