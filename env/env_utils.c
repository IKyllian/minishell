#include "../inc/minishell.h"

void	srch_and_dlt_env_var(t_env *env, char *to_search)
{
	int		i;
	t_env	*prev;

	prev = NULL;
	while (env)
	{
		i = 0;
		while (env->name[i] && to_search[i] && env->name[i] == to_search[i])
		{
			if (to_search[i + 1] == '\0')
			{
				if (prev && !env->next)
					prev->next = NULL;
				else if (prev && env->next)
					prev->next = env->next;
				free_list_item(env);
				return ;
			}
			i++;
		}
		prev = env;
		env = env->next;
	}
}

int	srch_and_rplce_env_var(t_env *env, char *to_search, char *new_value)
{
	int i;

	while (env)
	{
		i = 0;
		while (env->name[i] && to_search[i] && env->name[i] == to_search[i])
		{
			if (to_search[i + 1] == '\0')
			{
				free(env->value);
				env->value = new_value;
				return (1);
			}
			i++;
		}
		env = env->next;
	}
	return (0);
}

void	srch_and_dislay_env_var(t_env *env, char *to_search)
{
	int i;

	while (env)
	{
		i = 0;
		while (env->name[i] && to_search[i] && env->name[i] == to_search[i])
		{
			if (to_search[i + 1] == '\0')
			{
				ft_putstr_fd(env->value, 1);
				return ;
			}
			i++;
		}
		env = env->next;
	}
}