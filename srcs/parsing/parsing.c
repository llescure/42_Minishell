#include "../../include/minishell.h"

/*
 ** Main function that 1) launches the scanner, 2) the lexer, 3) proceeds to
 ** expansions with $ and between quotes and 4) finally the grammatical check
 */

int		parsing(char *user_input, t_shell *shell)
{
	//	int pid;
	//	int status;

	//	status = 0;
	if (user_input[0] == '\0')
		return (0);
	if (scanner(user_input, shell) < 0)
	{
		error_message("malloc");
		return (g_signal);
	}
	if (tokenizer(shell->token, shell) < 0)
	{
		error_message("malloc");
		return (g_signal);
	}
	clean_input(shell);
	ft_double_print_list(shell->token);
	ft_double_print_list(shell->type);
	printf("\n");
	if (join_clean_input(&shell->token, shell->type) < 0)
	{
		error_message("malloc");
		return (g_signal);
	}
	/*ft_double_free_list(&shell->type, 0);
	if (tokenizer(shell->token, shell) < 0)
	{
		error_message("malloc");
		return (g_signal);
	}*/
	ft_double_print_list(shell->token);
//	look_for_grammar_error(shell->token, shell->type, shell);
	/*
	   shell->cmd[0] = find_correct_path(shell->path, user_input);
	   pid = fork();
	   if (pid < 0)
	   return (-1);
	   else if (pid == 0)
	   {
	   if (ft_strncmp(user_input, "cat", ft_strlen("cat")) == 0)
	   {
	   if (execve(shell->cmd[0], shell->cmd, shell->env->env) < -1)
	   return (-1);
	   }
	   }
	   else
	   {
	   signal(SIGINT, handle_exec_signals);
	   signal(SIGQUIT, handle_exec_signals);
	   waitpid(pid, &status, 0);
	   signal(SIGINT, handle_signals);
	   signal(SIGQUIT, handle_signals);
	   }
	   g_signal = status;
	   if (g_signal == 2)
	   g_signal += 128;*/
	return (0);
}

int		clean_input(t_shell *shell)
{
	if (look_for_word_in_type(shell->type, "error") == 1)
	{
		error_message("syntax");
		return (g_signal);
	}
	if (look_for_word_in_type(shell->type, "single_quote") == 1)
		single_quote_expansion(shell, shell->type, &shell->token);
	if (look_for_word_in_type(shell->type, "double_quote") == 1)
		double_quote_expansion(shell, shell->type, &shell->token);
	if (look_for_word_in_type(shell->type, "expand") == 1)
		expand_expansion(shell, shell->type, &shell->token);
	if (g_signal < 0)
		error_message("malloc");
	return (g_signal);
}

int		join_clean_input(t_double_list **list, t_double_list *type)
{
	char	*new_str;
	char	*temp;

	while (type->next != NULL)
	{
		if (ft_strncmp(type->content, "single_quote", ft_strlen(type->content)) == 0
			|| ft_strncmp(type->content, "word", ft_strlen(type->content)) == 0
			|| ft_strncmp(type->content, "double_quote", ft_strlen(type->content)) == 0
			|| ft_strncmp(type->content, "expand", ft_strlen(type->content)) == 0)
		{
			new_str = ft_strdup((*list)->content);
			while (type->next != NULL && (ft_strncmp(type->next->content, "single_quote", ft_strlen(type->next->content)) == 0
			|| ft_strncmp(type->next->content, "word", ft_strlen(type->next->content)) == 0
			|| ft_strncmp(type->next->content, "double_quote", ft_strlen(type->next->content)) == 0
			|| ft_strncmp(type->next->content, "expand", ft_strlen(type->next->content)) == 0))
			{
				temp = new_str;
				new_str = ft_strjoin(new_str, (*list)->next->content);
				free(temp);
				type = type->next;
				*list = (*list)->next;
			}
		}
		printf("str = %s\n", new_str);
		if (type->next == NULL)
			break;
		type = type->next;
		*list = (*list)->next;
	}
	while ((*list)->previous != NULL)
		*list = (*list)->previous;
	return (0);
}

int		look_for_word_in_type(t_double_list *list, char *str)
{
	while (list != NULL)
	{
		if (ft_strncmp(list->content, str, ft_strlen(str)) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}

void	look_for_grammar_error(t_double_list *list, t_double_list *type,
		t_shell *shell)
{
	if (ft_strncmp(type->content, "command_option", ft_strlen(type->content)) == 0
			|| ft_strncmp(type->content, "word", ft_strlen(type->content)) == 0
			|| ft_strncmp(type->content, "pipe", ft_strlen(type->content)) == 0)
		return (error_message("command"));
	else if (ft_strncmp(type->content, "single_quote", ft_strlen(type->content)) == 0
			|| ft_strncmp(type->content, "double_quote", ft_strlen(type->content)) == 0
			|| ft_strncmp(type->content, "expand", ft_strlen(type->content)) == 0)
	{
		if (check_command(list->content, shell) == 0)
			return (error_message("command"));
	}
	while (list != NULL && type != NULL)
	{
		list = list->next;
		type = type->next;
	}
}
