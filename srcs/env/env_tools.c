/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 08:37:07 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/30 08:37:47 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_first_node(t_env	*first, t_env **env, t_env	*prev)
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
	free_env_list_item(*env);
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
