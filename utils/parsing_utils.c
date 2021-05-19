/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:44:20 by ctaleb            #+#    #+#             */
/*   Updated: 2021/05/19 14:46:56 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_quote(t_cmd *cmd, char c)
{
	if (is_quote(c))
	{
		if (c == 34 && !cmd->squote)
		{
			if (cmd->dquote)
				cmd->dquote = 0;
			else
				cmd->dquote = 1;
		}
		else if (c == 39 && !cmd->dquote)
		{
			if (cmd->squote)
				cmd->squote = 0;
			else
				cmd->squote = 1;
		}
	}
}