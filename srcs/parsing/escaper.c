/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:16:27 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/02 08:48:24 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	escape_and_increment(char **src, int *i)
{
	if ((*src)[*i] == '\\' && (*src)[*i + 1])
	{
		if ((*src)[*i + 1] == '\'' || (*src)[*i + 1] == '\"')
		{
			*src = char_remover(*src, *i);
		}
	}
	*i += 1;
}

int	escape_and_continue(t_cmd *cmd, char **src, int *i, int *j)
{
	*src = check_quote(cmd, *src, *i, 1);
	if (cmd->dquote || cmd->squote)
		*j += 1;
	if (*j == 1 && (cmd->squote || cmd->dquote))
		return (1);
	else if (*j > 0 && !cmd->squote && !cmd->dquote)
	{
		*j = 0;
		return (1);
	}
	return (0);
}

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
			if (escape_and_continue(cmd, &lst->value, &i, &j))
				continue ;
			escape_and_increment(&lst->value, &i);
		}
		if (cmd->squote || cmd->dquote)
		{
			ft_putstr_fd("Missing quotes\n", 2);
			return (0);
		}
		lst = lst->next;
	}
	return (1);
}
