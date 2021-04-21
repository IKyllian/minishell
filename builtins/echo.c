#include "../inc/minishell.h"

int	ft_echo(char *str)
{
	int	flag_exist;

	flag_exist = 0;
	if (str)
	{
		if (str[0] != '$')
			ft_putstr_fd(str, 1);
		// else
			// Check si une variable d'environnement est appelé 
	}
	if (!flag_exist)
		ft_putchar_fd('\n', 1);
	return (1);
}