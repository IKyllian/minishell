#include "../inc/minishell.h"

int	ft_cd(const char *path)
{
	return (chdir(path));
}