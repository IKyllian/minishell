/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:47:53 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/25 08:28:38 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_quotes(t_cmd *cmd, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 && cmd->squote == 0)
		{
			if (cmd->dquote)
				cmd->dquote = 0;
			else
				cmd->dquote = 1;
		}
		else if (line[i] == 39 && cmd->dquote == 0)
		{
			if (cmd->squote)
				cmd->squote = 0;
			else
				cmd->squote = 1;
		}
		i++;
	}
	if (cmd->dquote || cmd->squote)
		return (1);
	return (0);
}

int	quoting(t_cmd *cmd, char *line)
{
	if (line && !line[0])
		return (1);
	if (!cmd->line)
		cmd->line = ft_strdup(line);
	return (1);
}
