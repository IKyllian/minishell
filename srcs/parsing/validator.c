/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:57:48 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/30 10:12:39 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sendset_error(t_cmd *cmd)
{
	ft_putstr_fd("minishell: syntax error ne", cmd->fd_out);
	ft_putstr_fd("ar unexpected token '|'\n", cmd->fd_out);
	cmd->exit_status = 258;
}

int	type_check(t_shell *shell)
{
	t_pars	*lst;
	int		i;

	lst = shell->cmd.parsed;
	i = 1;
	while (lst)
	{
		if (lst->type == 3)
		{
			i = 0;
			lst = lst->next;
			continue ;
		}
		if (lst->type == 5 && i > 1)
			lst->type = 2;
		i++;
		lst = lst->next;
	}
	return (1);
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
	return (type_check(shell));
}
