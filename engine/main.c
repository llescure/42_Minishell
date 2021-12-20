int	ft_echo(char *str, char option)
{
	if (option != 'n')
	{
		printf("-%c", option)
	}
	printf("%s", str);
	if (option == 'n')
		return (0);
	else
		printf("\n");
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

int main(void)
{
	char str[100];

	while (1)
	{
		gets(str);
		if (ft_strncmp(str, "exit", len("exit") == 0)
			exit(0)
		if (ft_strncmp(str, "echo", len("echo")) == 0)
			ft_echo(str, option);
	}
}
