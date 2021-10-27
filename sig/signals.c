/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 07:59:44 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/27 12:38:58 by kdelport         ###   ########.fr       */
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
