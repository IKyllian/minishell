/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:46:40 by ctaleb            #+#    #+#             */
/*   Updated: 2021/04/30 17:12:26 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	tokenizer(t_cmd *cmd)
{
	int	i;
	int	j;
	int t;

	i = 0;
	j = dbl_array_len(cmd->history) - 1;
	t = 0;
	while (cmd->history[j][i])
	{
		i++;
		t++;
	}
	if (t == 0)
	{
		lstaddback_pars(&cmd->parsed, lstnew_pars(&cmd->history[j][i]));
		return (0);
	}
	else
	{
		lstaddback_pars(&cmd->parsed, lstnew_pars(ft_strndup(&cmd->history[j][i - t], t)));
		return (0);
	}
	return (0);
}