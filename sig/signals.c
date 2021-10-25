/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 07:59:44 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/22 13:05:02 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	p_sigkill(int sig)
{
	(void)sig;
	printf("\n");
}

void	p_sigquit(int sig)
{
	(void)sig;
	printf("Quit: %i\n", sig);
}

void	f_sigkill(int sig)
{
	(void)sig;
	exit(0);
}

void	f_sigquit(int sig)
{
	(void)sig;
	exit(0);
}

void	m_sigkill(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
	// shell->new_term.c_lflag &= ECHONL;
	shell->new_term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->new_term);
}

void	unset_term(t_shell *shell)
{
	// (void)shell;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->saved_term);
}
