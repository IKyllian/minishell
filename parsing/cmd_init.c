/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:02:29 by ctaleb            #+#    #+#             */
/*   Updated: 2021/04/29 13:05:18 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	cmd_init(void)
{
	t_cmd	cmd;

	cmd.history = NULL;
	cmd.parsed = NULL;
	cmd.exit_status = 0;
	cmd.fd = 1;
	return (cmd);
}