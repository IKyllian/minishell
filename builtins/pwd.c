#include "../inc/minishell.h"

int ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX))
		ft_putstr_fd(path, 1);
	else
	{
		ft_putstr_fd(strerror(errno), 1);
		ft_putchar_fd('\n', 1);
		return (0);
	}
	ft_putchar_fd('\n', 1);
	return (1);
}