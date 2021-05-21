/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:12:03 by ctaleb            #+#    #+#             */
/*   Updated: 2021/05/21 12:30:21 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	history_init(t_cmd *cmd)
{
	cmd->history = ft_calloc(sizeof(char *), 2);
	mem_check(cmd->history);
	cmd->history[0] = ft_strdup(cmd->line);
	mem_check(cmd->history[0]);
}

int	history_save(t_cmd *cmd, char *line)
{
	if (line && !line[0])
		return (0);
	if (!ft_strlen(cmd->line))
		return (-1);
	if (!cmd->history)
		history_init(cmd);
	else
		cmd->history = dbl_array_add(cmd->history, cmd->line);
	free(cmd->line);
	cmd->line = NULL;
	return (0);
}