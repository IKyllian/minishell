/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:57:48 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/27 16:05:28 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sendset_error(t_cmd *cmd)
{
	ft_putstr_fd("minishell: syntax error ne", cmd->fd_out);
	ft_putstr_fd("ar unexpected token '|'\n", cmd->fd_out);
	cmd->exit_status = 258;
}

int	validator(t_shell *shell)
{
	t_pars	*lst;

	lst = shell->cmd.parsed;
	if (lst && lst->type == 2)
		lst->type = 1;
	if (lst && lst->type == 3)
	{
		sendset_error(&shell->cmd);
		return (0);
	}
	while (lst)
	{
		if (lst->type == 3)
		{
			if (lst->next && lst->next->type == 2)
				lst->next->type = 1;
			else if ((lst->next && lst->next->type == 3) || !lst->next)
			{
				sendset_error(&shell->cmd);
				return (0);
			}
		}
		lst = lst->next;
	}
	return (1);
}
