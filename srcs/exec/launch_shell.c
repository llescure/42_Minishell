#include "../../include/minishell.h"

void	create_new_line(int signum)
{
	(void)signum;
	rl_on_new_line();
	ft_putstr_fd("\n", 1);
	rl_redisplay();
}

void	launch_shell(t_shell *shell)
{
	char	*user_input;
	struct	sigaction new_action;

	user_input = NULL;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		new_action.sa_handler = create_new_line;
		sigaction(SIGINT, &new_action, NULL);
		if (user_input != NULL)
		{
			free(user_input);
			user_input = NULL;
		}
		user_input = readline("my_minishell# ");
		if (user_input != NULL)
			add_history(user_input);
		else
		{
			free_all(shell);
			ft_putstr_fd("exit\n", 1);
			return ;
		}
	}
}
