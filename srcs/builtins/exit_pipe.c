/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 10:52:00 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/30 11:24:52 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit_pipe(t_shell *shell, t_pars **cmd_parsed)
{
	int	ret;

	ret = 0;
	unset_term(shell);
	if (shell->line)
		shell->cmd.exit_status = get_exit_nb(shell, cmd_parsed);
}
