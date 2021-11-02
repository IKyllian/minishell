/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:12:03 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/02 12:42:35 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	history_init(t_cmd *cmd, t_shell *shell)
{
	cmd->history = ft_calloc(sizeof(char *), 2);
	mem_check(shell, cmd->history);
	cmd->history[0] = ft_strdup(cmd->line);
	mem_check(shell, cmd->history[0]);
}

int	history_save(t_cmd *cmd, char *line, t_shell *shell)
{
	if (line && !line[0])
		return (0);
	if (!ft_strlen(cmd->line))
		return (-1);
	if (!cmd->history)
	{
		add_history(cmd->line);
		history_init(cmd, shell);
	}
	else
	{
		add_history(cmd->line);
		cmd->history = dbl_array_add(cmd->history, cmd->line, shell);
	}
	free(cmd->line);
	cmd->line = NULL;
	return (0);
}
