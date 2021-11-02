/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pars_manage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:37:06 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/02 15:05:31 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*lst_replace(t_pars *lst, t_pars *new_tokens, int *t)
{
	t_pars	*temp;
	t_pars	*browse;

	temp = NULL;
	if (lst->next->next)
		temp = lst->next->next;
	browse = new_tokens;
	free(lst->next->value);
	free(lst->next);
	lst->next = new_tokens;
	while (browse->next)
		browse = browse->next;
	browse->next = temp;
	*t += lstsize_pars(new_tokens);
	return (temp);
}

t_pars	*lst_replace_start(t_cmd *cmd, t_pars *new_tokens, int	*t)
{
	t_pars	*temp;
	t_pars	*browse;

	temp = cmd->parsed->next;
	browse = new_tokens;
	free(cmd->parsed->value);
	free(cmd->parsed);
	cmd->parsed = new_tokens;
	while (browse->next)
		browse = browse->next;
	browse->next = temp;
	*t += lstsize_pars(new_tokens);
	return (temp);
}

void	lstdel_beg_pars(t_pars **lst)
{
	t_pars	*temp;

	if (lstsize_pars(*lst) == 2)
		lstclear_pars(lst);
	else
	{
		temp = (*lst)->next->next;
		free((*lst)->next->value);
		free((*lst)->value);
		free((*lst)->next);
		free((*lst));
		*lst = temp;
	}
}

void	lstdel_other_pars(t_pars **lst, int d)
{
	t_pars	*temp;
	t_pars	*pars;
	int		i;

	pars = *lst;
	i = 0;
	temp = NULL;
	while (pars)
	{
		if (i == d - 1)
		{
			if ((pars)->next->next->next)
				temp = (pars)->next->next->next;
			free((pars)->next->next->value);
			free((pars)->next->value);
			free((pars)->next->next);
			free((pars)->next);
			pars->next = temp;
			return ;
		}
		pars = pars->next;
		i++;
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
		if ((*lst)->value)
			free((*lst)->value);
		if (*lst)
			free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
