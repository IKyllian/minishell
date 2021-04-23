/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:12:03 by ctaleb            #+#    #+#             */
/*   Updated: 2021/04/22 13:46:26 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	history_init(t_cmd *cmd, char *line)
{
	cmd->history = ft_calloc(sizeof(char *), 2);
	mem_check(cmd->history);
	cmd->history[0] = ft_strdup(line);
	mem_check(cmd->history[0]);
}

int	history_save(t_cmd *cmd, char *line)
{
	if (!ft_strlen(line))
		return (-1);
	if (!cmd->history)
		history_init(cmd, line);
	else
		cmd->history = dbl_array_add(cmd->history, line);
	return (0);
}