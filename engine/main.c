#include "minishell.h"

int	ft_echo(char *str, char option)
{
	if (option != 'n')
	{
		printf("-%c", option);
	}
	printf("%s", str);
	if (option == 'n')
		return (0);
	else
		printf("\n");
	printf("hey\n");
	return (0);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int main(void)
{
	char *cmd = "echo";
	char option = 'n';
	char *str = "coucou";

	while (1)
	{
		char *coucou = strcpy(str,cmd);
		//char *command = tgetstr("echo", NULL);
		//printf("%s\n", command);
		if (ft_strncmp(cmd, "exit", ft_strlen("exit") == 0))
			exit(0);
		if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
			ft_echo(str, option);
	}
	return (0);
}
