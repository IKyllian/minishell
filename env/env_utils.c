/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:58:56 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/25 10:34:43 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (to_search[i + 1] == '\0' && env->name[i + 1] == '\0')
			{
				if (prev && !env->next)
					prev->next = NULL;
				else if (prev && env->next)
					prev->next = env->next;
				free_env_list_item(env);
				return ;
			}
			i++;
		}
		prev = env;
		env = env->next;
	}
}

int	srch_and_rplce_env_var(t_env *env, char *to_search, char *new_value, int mode)
{
	int i;

	while (env)
	{
		i = 0;
		while (env->name[i] && to_search[i] && env->name[i] == to_search[i])
		{
			if (to_search[i + 1] == '\0' && env->name[i + 1] == '\0')
			{
				if (mode == 0)
				{
					if (env->value)
						free(env->value);
					env->value = new_value;
				}
				else
					env->value = ft_strjoin(env->value, new_value); // Besoin de free l'ancienne value
				return (1);
			}
			i++;
		}
		env = env->next;
	}
	return (0);
}

void	srch_and_dislay_env_var(t_env *env, char *to_search, int fd)
{
	int i;

	while (env)
	{
		i = 0;
		while (env->name[i] && to_search[i] && env->name[i] == to_search[i])
		{
			if (to_search[i + 1] == '\0' && env->name[i + 1] == '\0')
			{
				ft_putstr_fd(env->value, fd);
				return ;
			}
			i++;
		}
		env = env->next;
	}
}

t_env	*srch_and_return_env_var(t_env *env, char *to_search)
{
	int i;

	while (env)
	{
		i = 0;
		while (env->name[i] && to_search[i] && env->name[i] == to_search[i])
		{
			if (to_search[i + 1] == '\0' && env->name[i + 1] == '\0')
				return (env);
			i++;
		}
		env = env->next;
	}
	return (NULL);
}