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
		error_message("malloc", shell->fd_outfile);
		free_all(shell);
		return (g_signal);
	}
	if (tokenizer(shell->token, shell) < 0)
	{
		error_message("malloc", shell->fd_outfile);
		free_all(shell);
		return (g_signal);
	}
//	ft_double_print_list(shell->token);
//	ft_double_print_list(shell->type);
	if (clean_input(shell) != 0)
		return (g_signal);
//	printf("\n");
	if (join_clean_input(&shell->token, shell->type) < 0)
	{
		error_message("malloc", shell->fd_outfile);
		free_all(shell);
		return (g_signal);
	}
	ft_double_free_list(&shell->type, 0);
	if (tokenizer(shell->token, shell) < 0)
	  {
		error_message("malloc", shell->fd_outfile);
		free_all(shell);
		return (g_signal);
	  }
//	ft_double_print_list(shell->token);
//	ft_double_print_list(shell->type);
	look_for_grammar_error(shell->type, shell->fd_outfile);
	shell->token_bis = create_tab_from_linked_list(shell->token);
	shell->type_bis = create_tab_from_linked_list(shell->type);
//	print_tab(shell->token_bis);
//	print_tab(shell->type_bis);
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
		error_message("syntax", shell->fd_outfile);
		return (g_signal);
	}
	if (look_for_word_in_type(shell->type, "single_quote") == 1)
		single_quote_expansion(shell, shell->type, &shell->token);
	if (look_for_word_in_type(shell->type, "double_quote") == 1)
		double_quote_expansion(shell, shell->type, &shell->token);
	if (look_for_word_in_type(shell->type, "expand") == 1)
		expand_expansion(shell, shell->type, &shell->token);
	if (g_signal < 0)
	{
		error_message("malloc", shell->fd_outfile);
		return (g_signal);
	}
	return (0);
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
		if (ft_strncmp(type->content, "white_space", ft_strlen(type->content)) == 0)
		{
			str_temp = (*list)->content;
			(*list)->content = ft_strdup(" ");
			free(str_temp);
		}
		type = type->next;
		*list = (*list)->next;
	}
	while ((*list)->previous != NULL)
		*list = (*list)->previous;
	return (0);
}

void	look_for_grammar_error(t_double_list *type, int fd_outfile)
{
	if (look_for_word_in_type(type, "heredoc") == 0 &&
		(ft_strncmp(type->content, "command_option",
		ft_strlen("command_option")) == 0
		|| ft_strncmp(type->content, "word", ft_strlen(type->content)) == 0
		|| ft_strncmp(type->content, "expand", ft_strlen(type->content)) == 0))
		return (error_message("command", fd_outfile));
	else if ((ft_strncmp(type->content, "redir_right", ft_strlen(type->content)) == 0
		|| ft_strncmp(type->content, "redir_left", ft_strlen(type->content)) == 0
		|| ft_strncmp(type->content, "heredoc", ft_strlen(type->content)) == 0
		|| ft_strncmp(type->content, "d_redir_right", ft_strlen(type->content)) == 0)
		&& type->next == NULL)
		return (error_message("syntaxe", fd_outfile));
	else if (ft_strncmp(type->content, "pipe", ft_strlen(type->content)) == 0)
		return (error_message("syntaxe", fd_outfile));
}

char	**create_tab_from_linked_list(t_double_list *list)
{
	char	**tab_cpy;
	int		i;

	tab_cpy = malloc(sizeof(char *) * (ft_double_lstsize(list) + 1));
	if (tab_cpy == NULL)
		return (NULL);
	i = 0;
	while (list != NULL)
	{
		tab_cpy[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	tab_cpy[i] = NULL;
	return (tab_cpy);
}
