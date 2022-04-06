#include "../../include/minishell.h"

int	prompt(char **user_input, t_shell *shell)
{
	char	*lign;

	lign = *user_input;
	if (lign != NULL)
	{
		if (lign[0] != '\0')
		{
			free_token(&shell->token);
			free_command(&shell->command);
		}
		free(lign);
		lign = NULL;
	}
	lign = readline("my_minishell# ");
	if (lign != NULL)
		add_history(lign);
	else
	{
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
	int		parsing_output;

	user_input = NULL;
	shell->token = NULL;
	shell->command = NULL;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	while (1)
	{
		if (prompt(&user_input, shell) != 0)
			return (g_signal);
		parsing_output = parsing(user_input, shell);
		if (parsing_output < 0)
			return (g_signal);
		if (*user_input != '\0' && parsing_output == 0)
			execute_input(shell, shell->token, shell->command);
	}
}
