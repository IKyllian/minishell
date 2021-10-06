/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 07:59:44 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/05 10:25:36 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	f_sigkill(int sig)
{
	(void)sig;
	signal(SIGINT, f_sigkill);
	kill(g_pid, SIGKILL);
	printf("\n");
}

void	f_sigquit(int sig)
{
	printf("Quit: %i\n", sig);
	signal(SIGQUIT, f_sigquit);
	kill(g_pid, SIGQUIT);
}

void	m_sigkill(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_term(t_shell *shell)
{
	tcgetattr(0, &shell->new_term);
	shell->new_term.c_cc[VQUIT] = 0;//ctrl-backslash
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->new_term);
}

void	unset_term(t_shell *shell)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->saved_term);
}
