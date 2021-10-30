/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 08:34:30 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/30 08:35:28 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	end_cd(t_shell *shell, t_pars **cmd_parsed)
{
	if (errno != 14)
		print_error(errno);
	shell->cmd.exit_status = 1;
	(*cmd_parsed) = (*cmd_parsed)->next;
	return (1);
}
