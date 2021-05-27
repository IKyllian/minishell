/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:16:27 by ctaleb            #+#    #+#             */
/*   Updated: 2021/05/27 14:53:26 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	search_and_escape(t_cmd *cmd)
{
	int	i;
	int	j;
	t_pars	*lst;

	cmd->squote = 0;
	cmd->dquote = 0;
	lst = cmd->parsed;
	while(lst)
	{
		j = 0;
		i = 0;
		while(lst->value[i])
		{
			lst->value = check_quote(cmd, lst->value, i, 1);
			if (cmd->dquote || cmd->squote)
				j++;
			if (j == 1 && (cmd->squote || cmd->dquote))
				continue ;
			else if (j > 0 && !cmd->squote && !cmd->dquote)
			{
				j = 0;
				continue ;
			}
			if (lst->value[i] == '\\' && lst->value[i + 1])
			{
				if (cmd->squote)
				{
					i++;
					continue ;
				}
				else if (cmd->dquote && is_escapable(lst->value[i + 1]))
					lst->value = char_remover(lst->value, i);
				else
					lst->value = char_remover(lst->value, i);
			}
			i++;
		}
		lst = lst->next;
	}
}
