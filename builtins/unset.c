#include "../inc/minishell.h"

int	ft_unset(t_env *env, char **arg)
{
	srch_and_dlt_env_var(env, arg[1]);
	return (0);
}