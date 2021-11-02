/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:49:37 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/02 08:48:24 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redir(t_redir *redir, int p_i, char *value, int type)
{
	redir->pipe_index = p_i;
	redir->value = ft_strdup(value);
	redir->type = type;
}

int	redirect_comparator(t_pars *lst, t_cmd *cmd, int *j, int p_i)
{
	if (!lst->next || lst->next->type != 2)
	{
		ft_putstr_fd("minishell: syntax error ne", cmd->fd_out);
		ft_putstr_fd("ar unexpected token\n", cmd->fd_out);
		cmd->exit_status = 258;
		return (0);
	}
	if (!ft_strncmp(lst->value, ">>", 2))
	{
		set_redir(&cmd->redir[*j], p_i, lst->next->value, 3);
		*j += 1;
	}
	else if (!ft_strncmp(lst->value, "<", 1))
	{
		set_redir(&cmd->redir[*j], p_i, lst->next->value, 1);
		*j += 1;
	}
	else if (!ft_strncmp(lst->value, ">", 1))
	{
		set_redir(&cmd->redir[*j], p_i, lst->next->value, 2);
		*j += 1;
	}
	return (1);
}
