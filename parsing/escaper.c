/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:16:27 by ctaleb            #+#    #+#             */
/*   Updated: 2021/05/19 14:02:35 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	search_and_escape(t_cmd *cmd)
{
	int	i;

	cmd->squote = 0;
	cmd->dquote = 0;
	while(cmd->parsed)
	{
		i = 0;
		while(cmd->parsed->value[i])
		{
			if (cmd->parsed->value[i] == '\\' && cmd->parsed->value[i + 1])
			{
				
			}
			i++;
		}
	}
}
