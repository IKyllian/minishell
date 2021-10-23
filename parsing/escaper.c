/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:16:27 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/22 16:20:07 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	search_browse(t_cmd *cmd, int *i, int *j)
// {
	
// }

int	search_and_escape(t_cmd *cmd)
{
	int		i;
	int		j;
	t_pars	*lst;

	cmd->squote = 0;
	cmd->dquote = 0;
	lst = cmd->parsed;
	while (lst)
	{
		j = 0;
		i = 0;
		while (lst->value[i])
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
			i++;
		}
		if (cmd->squote || cmd->dquote)
		{
			printf("Missing quotes\n");
			return (0);
		}
		lst = lst->next;
	}
	return (1);
}
