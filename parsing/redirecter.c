/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:13:22 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/27 14:21:24 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	extract_redirect(t_cmd *cmd)
{
	t_pars	*lst;
	int		p_i;
	int		i;
	int		j;

	lst = cmd->parsed;
	p_i = 0;
	i = 0;
	j = 0;
	while (lst)
	{
		if (lst->type == 3)
			p_i++;
		if (lst->type == 4 && ft_strncmp(lst->value, "<<", 2))
		{
			if (!redirect_comparator(lst, cmd, &j, p_i))
				return (0);
		}
		lst = lst->next;
		i++;
	}
	return (1);
}

int	clean_pars(t_cmd *cmd)
{
	t_pars	*lst;
	int		i;

	lst = cmd->parsed;
	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->type == 4 && ft_strncmp(lst->value, "<<", 2))
		{
			if (!i)
				lstdel_beg_pars(&cmd->parsed);
			else
				lstdel_other_pars(&cmd->parsed, i);
			return (1);
		}
		lst = lst->next;
		i++;
	}
	return (0);
}

int	check_redir(t_cmd *cmd)
{
	t_pars	*lst;

	lst = cmd->parsed;
	cmd->recount = 0;
	while (lst)
	{
		if (lst->type == 4)
		{
			if (ft_strncmp(lst->value, "<<", 2))
				cmd->recount++;
		}
		lst = lst->next;
	}
	return (1);
}

int	redirect(t_cmd *cmd)
{
	if (!check_redir(cmd))
		return (0);
	cmd->redir = ft_calloc(cmd->recount + 1, sizeof(t_redir));
	if (!cmd->recount)
		return (1);
	if (!extract_redirect(cmd))
		return (0);
	while (clean_pars(cmd))
		continue ;
	return (1);
}
