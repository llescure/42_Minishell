#include "../../include/minishell.h"

void	create_new_line(int signum)
{
	(void)signum;
	rl_on_new_line();
	ft_putstr_fd("\n", 1);
	rl_redisplay();
	g_signal = -1;
}

int	handle_signal(char **user_input, t_shell *shell)
{
	char	*lign;

	lign = *user_input;
	signal(SIGQUIT, SIG_IGN);
	if (lign != NULL)
	{
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

void	launch_shell(t_shell *shell)
{
	char	*user_input;
	struct	sigaction new_action;

	user_input = NULL;
	ft_memset(&new_action, 0, sizeof(new_action));
	while (1)
	{
		new_action.sa_handler = create_new_line;
		sigaction(SIGINT, &new_action, NULL);
		if (handle_signal(&user_input, shell) < 0)
			return ;
		parsing(user_input, shell);
	}
}
