/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:36:50 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/27 12:38:43 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sighandler(int sig)
{
	(void)sig;
	printf("\n");
	g_heredoc = 0;
}

void	set_term(t_shell *shell)
{
	tcgetattr(0, &shell->new_term);
	shell->new_term.c_lflag &= ~ECHOCTL;
	shell->new_term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->new_term);
}

void	unset_term(t_shell *shell)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->saved_term);
}
