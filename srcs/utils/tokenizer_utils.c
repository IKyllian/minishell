/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 08:18:29 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/02 08:48:24 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	long_operator(t_cmd *cmd, int *i, int *j, int *t)
{
	if (*i >= 1 && cmd->history[*j][*i - 1] != ' ')
		lstaddback_pars(&cmd->parsed,
			lstnew_pars(ft_strndup(&cmd->history[*j][*i - *t], *t + 1)));
	if (cmd->history[*j][*i] == ' ')
		*i += 1;
	*t = 0;
}

void	short_operator(t_cmd *cmd, int *i, int *j, int *t)
{
	if (*i >= 1 && cmd->history[*j][*i - 1] != ' ')
		lstaddback_pars(&cmd->parsed,
			lstnew_pars(ft_strndup(&cmd->history[*j][*i - *t], *t)));
	if (cmd->history[*j][*i] == ' ')
		*t = 0;
	else
		*t = 1;
}

void	operator(t_cmd *cmd, int *i, int *j, int *t)
{
	if (*i >= 1 && cmd->history[*j][*i - 1] != ' ' && *t > 0)
		lstaddback_pars(&cmd->parsed,
			lstnew_pars(ft_strndup(&cmd->history[*j][*i - *t], *t)));
	*t = 1;
}

void	endofline(t_cmd *cmd, int *i, int *j, int *t)
{
	if (*i >= 1 && cmd->history[*j][*i - 1] != ' ')
		lstaddback_pars(&cmd->parsed,
			lstnew_pars(ft_strndup(&cmd->history[*j][*i - *t], *t)));
	*t = 0;
}

void	space(t_cmd *cmd, int *i, int *j, int *t)
{
	if (*i >= 1 && cmd->history[*j][*i - 1] != ' ' && *t != 0)
		lstaddback_pars(&cmd->parsed,
			lstnew_pars(ft_strndup(&cmd->history[*j][*i - *t], *t)));
	*t = 0;
}
