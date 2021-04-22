/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/22 13:46:56 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int main(void)
{
	int		exit;
	char 	*line;
	t_cmd	cmd;

	exit = 0;
	line = NULL;
	cmd = cmd_init();
	ft_putstr_fd("minishell-0.1$ ", 1);
	while (ft_get_next_line(0, 5, &line))
	{
		history_save(&cmd, line);	
		if (!strncmp(line, "pwd", 3))
			ft_pwd();
		if (!strncmp(line, "exit", 5))
		{
			exit = 0;
			break ;
		}
		free(line);
		line = NULL;
		ft_putstr_fd("minishell-0.1$ ", 1);
	}
	dbl_array_print(cmd.history);
	return (exit);
}
