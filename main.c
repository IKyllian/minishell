/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/20 15:47:53 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	int		exit;
	char 	*line;

	exit = 0;
	line = NULL;
	while (!exit)
	{
		while (ft_get_next_line(0, 5, &line))
		{
			ft_putstr_fd(line, 1);
			ft_putstr_fd("\n", 1);
			if (!strncmp(line, "exit", 5))
			{
				exit = 1;
				break ;
			}
			free(line);
			line = NULL;
		}
	}
	return (0);
}
