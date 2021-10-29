/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:58:56 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/29 18:19:29 by kdelport         ###   ########.fr       */
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
		while ((*env)->name[i] && to_search[i] && (*env)->name[i] == to_search[i])
		{
			if (to_search[i + 1] == '\0' && (*env)->name[i + 1] == '\0')
			{
				if (ft_strcmp(first->name, (*env)->name) == 0)
				{
					*env = (*env)->next;
					free(first->name);
					if (first->value)
						free(first->value);
					free(first);
					first = NULL;
					return ;
				}
				if (prev && !(*env)->next)
					prev->next = NULL;
				else if (prev && (*env)->next)
					prev->next = (*env)->next;
				// free_env_list_item(env);
				free((*env)->name);
				if ((*env)->value)
					free((*env)->value);
				free(*env);
				*env = NULL;
				*env = first;
				return ;
			}
			i++;
		}
		prev = *env;
		*env = (*env)->next;
	}
	*env = first;
}

void	replace_env_var(t_env *env, char *new_val, int mode)
{
	char	*temp;

	if (mode == 1 && env->value)
	{
		temp = env->value;
		env->value = ft_strjoin(env->value, new_val);
		free(new_val);
		free(temp);
	}
	else
	{
		if (env->value)
			free(env->value);
		env->value = new_val;
	}
}

int	srch_and_rplce_env_var(t_env *env, char *to_srch, char *new, int mode)
{
	int		i;

	while (env)
	{
		i = 0;
		while (env->name[i] && to_srch[i] && env->name[i] == to_srch[i])
		{
			if (to_srch[i + 1] == '\0' && env->name[i + 1] == '\0')
			{
				replace_env_var(env, new, mode);
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
	int	i;

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
	int	i;

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
