/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:36:50 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/29 08:39:33 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ign_sigkill(int sig)
{
	(void)sig;
	g_heredoc = 1;
}

void	ign_sigquit(int sig)
{
	(void)sig;
	g_heredoc = 2;
}

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
	g_heredoc = 0;
}