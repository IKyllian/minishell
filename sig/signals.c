/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 07:59:44 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/15 11:39:30 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	p_sigkill(int sig)
{
	// int	i;

	// i = g_pids.count - 1;
	// if (g_pids.mode != 2)
	// 	return ;
	// while (i >= 0)
	// {
	// 	// printf("pid:%i\n", g_pids.pid[i].pid);
	// 	if (g_pids.pid[i].pid)
	// 		kill(g_pids.pid[i].pid, SIGINT);
	// 	i--;
	// }
	(void)sig;
	printf("\n");
}

void	p_sigquit(int sig)
{
	// int	i;

	// i = g_pids.count - 1;
	// if (g_pids.mode != 2)
	// 	return ;
	// while (i >= 0)
	// {
	// 	// if (g_pids.pid[i].pid)
	// 		kill(g_pids.pid[i].pid, SIGQUIT);
	// 	i--;
	// }
	(void)sig;
	printf("Quit: %i\n", sig);
}

void	f_sigkill(int sig)
{
	(void)sig;
	// signal(SIGQUIT, &f_sigkill);
	// if (g_pids.mode != 1)
	// 	return ;
	// printf("\n");
	// kill(g_pids.spid, SIGINT);
	exit(0);
}

void	f_sigquit(int sig)
{
	(void)sig;
	// signal(SIGQUIT, &f_sigquit);
	// if (g_pids.mode != 1)
	// 	return ;
	// printf("Quit: %i\n", sig);
	// kill(g_pids.spid, SIGQUIT);
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
