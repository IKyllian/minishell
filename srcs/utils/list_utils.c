/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:57:05 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/03 08:18:13 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_env(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_env	*ft_lstnew_env(char *name, char *value, t_shell *shell)
{
	t_env	*env;

	env = malloc(sizeof(t_env) * 1);
	mem_check(shell, env);
	if (!env)
		return (NULL);
	env->name = name;
	env->value = value;
	env->next = NULL;
	return (env);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	int	i;
	int	max;

	i = 0;
	max = ft_lstsize_env(lst);
	while (i < max - 1)
	{
		i++;
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = ft_lstlast_env(*alst);
	tmp->next = new;
}
