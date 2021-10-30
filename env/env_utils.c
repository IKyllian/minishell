/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:58:56 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/30 08:37:30 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	srch_and_dlt_env_var(t_env **env, char *to_search)
{
	int		i;
	t_env	*prev;
	t_env	*first;

	prev = NULL;
	first = *env;
	while (*env)
	{
		i = 0;
		if (ft_strcmp((*env)->name, to_search) == 0)
		{
			check_first_node(first, env, prev);
			return ;
		}
		i++;
		prev = *env;
		*env = (*env)->next;
	}
	*env = first;
}

int	srch_and_rplce_env_var(t_env *env, char *to_srch, char *new, int mode)
{
	int		i;

	while (env)
	{
		i = 0;
		if (ft_strcmp(env->name, to_srch) == 0)
		{
			replace_env_var(env, new, mode);
			return (1);
		}
		i++;
		env = env->next;
	}
	return (0);
}

void	srch_and_dislay_env_var(t_env *env, char *to_search, int fd)
{
	int	i;

	while (env)
	{
		i = 0;
		if (ft_strcmp(env->name, to_search) == 0)
		{
			ft_putstr_fd(env->value, fd);
			return ;
		}
		i++;
		env = env->next;
	}
}

t_env	*srch_and_return_env_var(t_env *env, char *to_search)
{
	int	i;

	while (env)
	{
		i = 0;
		if (ft_strcmp(env->name, to_search) == 0)
			return (env);
		i++;
		env = env->next;
	}
	return (NULL);
}
