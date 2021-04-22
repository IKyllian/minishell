/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/22 16:33:29 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int main(int argc, char **argv, char **env)
{
	int		exit;
	char 	*line;
	t_env	env_s;

	(void)argc;
	(void)argv;
	exit = 0;
	line = NULL;
	env_s = env_init(env);
	ft_putstr_fd("minishell-0.1$ ", 1);
	while (ft_get_next_line(0, 5, &line))
	{
		// ft_putstr_fd(line, 1);
		// ft_putstr_fd("\n", 1);
		if (!strncmp(line, "pwd", 3))
			ft_pwd();
		else if (!strncmp(line, "export", 6))
			ft_export(&env_s);
		else if (!strncmp(line, "exit", 5))
		{
			exit = 0;
			break ;
		}
		else
			ft_cd(line, &env_s);
			// ft_echo(line);
		free(line);
		line = NULL;
		ft_putstr_fd("minishell-0.1$ ", 1);
	}
	return (exit);
}
