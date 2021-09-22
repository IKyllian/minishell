/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:16:27 by ctaleb            #+#    #+#             */
/*   Updated: 2021/09/22 11:18:40 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	search_and_escape(t_cmd *cmd)
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
			if (!lst->value[i + 1] && (cmd->dquote || cmd->squote) && (lst->value[i] != '\"' && lst->value[i] != '\''))
				return (0);
			if (cmd->dquote || cmd->squote)
				j++;
			if (j == 1 && (cmd->squote || cmd->dquote))
				continue ;
			else if (j > 0 && !cmd->squote && !cmd->dquote)
			{
				j = 0;
				continue ;
			}
			// printf("%c\n", lst->value[i]);
			/*if (lst->value[i] == '\\' && lst->value[i + 1])
			{
				// printf("%i\tsq%i\tdq%i\n", i, cmd->squote, cmd->dquote);
				if (cmd->squote)
				{
					i++;
					continue ;
				}
				else if (cmd->dquote && is_escapable(lst->value[i + 1]))
					lst->value = char_remover(lst->value, i);
				else
					lst->value = char_remover(lst->value, i);
			}*/
			i++;
		}
		lst = lst->next;
	}
	return (1);
}
