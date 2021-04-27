#include "../inc/minishell.h"

//Exit status = 0 if no error
int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value != NULL)
		{
			ft_putstr_fd(env->name, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(env->value, 1);
			ft_putchar_fd('\n', 1);
		}
		env = env->next;
	}
	return (0);
}