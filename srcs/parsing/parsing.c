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
	ft_double_free_list(&shell->type, 0);
	if (tokenizer(shell->token, shell) < 0)
	  {
		  error_message("malloc");
		  return (g_signal);
	  }
	ft_double_print_list(shell->token);
	ft_double_print_list(shell->type);
	look_for_grammar_error(shell->token, shell->type);
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
	char	*str_temp;

	while (type->next != NULL)
	{
		if (special_condition_cara_is_respected(type->content) == 1)
		{
			while (type->next != NULL &&
				special_condition_cara_is_respected(type->next->content) == 1)
			{
				str_temp = (*list)->content;
				(*list)->content = ft_strjoin(str_temp, (*list)->next->content);
				free(str_temp);
				delete_node(list, 1);
				delete_node(&type, 0);
			}
		}
		if (type->next == NULL)
			break;
		type = type->next;
		*list = (*list)->next;
	}
	while ((*list)->previous != NULL)
		*list = (*list)->previous;
	return (0);
}

int		special_condition_cara_is_respected(char *str)
{
	if (ft_strncmp(str, "single_quote", ft_strlen(str)) == 0
			|| ft_strncmp(str, "word", ft_strlen(str)) == 0
			|| ft_strncmp(str, "double_quote", ft_strlen(str)) == 0
			|| ft_strncmp(str, "expand", ft_strlen(str)) == 0)
		return (1);
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

void	look_for_grammar_error(t_double_list *list, t_double_list *type)
{
	if (ft_strncmp(type->content, "command_option", ft_strlen(type->content)) == 0
		|| ft_strncmp(type->content, "word", ft_strlen(type->content)) == 0)
		return (error_message("command"));
	else if ((ft_strncmp(type->content, "redir_right", ft_strlen(type->content)) == 0
		|| ft_strncmp(type->content, "redir_left", ft_strlen(type->content)) == 0
		|| ft_strncmp(type->content, "heredoc", ft_strlen(type->content)) == 0
		|| ft_strncmp(type->content, "d_redir_right", ft_strlen(type->content)) == 0)
		&& type->next == NULL)
		return (error_message("syntaxe"));
	else if (ft_strncmp(type->content, "pipe", ft_strlen(type->content)) == 0)
		return (error_message("syntaxe"));
}
