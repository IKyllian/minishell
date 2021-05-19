/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pars_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:44:29 by ctaleb            #+#    #+#             */
/*   Updated: 2021/05/18 15:34:18 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lstput_pars(t_pars *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		printf("*%i\t%s\t%i*\n", i, lst->value, lst->type);
		i++;
		lst = lst->next;
	}
}

void	lstclear_pars(t_pars **lst)
{
	t_pars	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->value);
		free(*lst);
		*lst = temp;
		
	}
	*lst = NULL;
}

int		lstsize_pars(t_pars *lst)
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

t_pars	*lstnew_pars(char *value)
{
	t_pars	*parsed;

	parsed = ft_calloc(1, sizeof(t_pars));
	mem_check(parsed);
	parsed->value = value;
	parsed->type = type_set(value);
	parsed->next = NULL;
	return (parsed);
}

t_pars	*lstlast_pars(t_pars *lst)
{
	int	i;
	int	max;

	i = 0;
	max = lstsize_pars(lst);
	while (i < max - 1)
	{
		i++;
		lst = lst->next;
	}
	return (lst);
}

void	lstaddback_pars(t_pars **alst, t_pars *new)
{
	t_pars	*tmp;

	if (!new)
		return ;
	if (!*alst)
	{
		if (new->type == 2)
			new->type = 1;
		*alst = new;
		return ;
	}
	tmp = lstlast_pars(*alst);
	if ((tmp->type == 3 || tmp->type == 5) && new->type == 2)
		new->type = 1;
	tmp->next = new;
}
