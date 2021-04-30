/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:31 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/30 15:41:18 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(char *str)
{
	char *env_var;
	int	flag_exist;

	flag_exist = 0;
	if (str)
	{
		if (str[0] != '$')
			ft_putstr_fd(str, 1);
		else
		{
			if (str[1] == ' ')
				ft_putstr_fd(str, 1);
			else
			{
				env_var = getenv(str + 1);
				if (env_var != NULL)
					ft_putstr_fd(env_var, 1);
			}
		} 
	}
	if (!flag_exist)
		ft_putchar_fd('\n', 1);
	return (1);
}

//Exit status = 0 if no error
// int	ft_echo(char **arg, t_env *env, t_cmd *cmd)
// {
// 	int i;
// 	int	flag_exist;

// 	flag_exist = 0;
// 	i = -1;
// 	while (arg[++i])
// 	{	
// 		if (i == 1 && ft_strcmp(arg[i], "-n") == 0)
// 			flag_exist = 1;
// 		if (arg[i][0] == '$' && arg[i][1] != ' ')
// 			srch_and_dislay_env_var(env, arg[i]);
// 		// else if (arg[i][0] == '$' && arg[i][1] != '?')
// 			// ft_putnbr_fd(cmd->exit_status, cmd->fd);
// 		else
// 		{
// 			ft_putstr_fd(arg[i], cmd->fd);
// 			ft_putchar_fd(' ', cmd->fd);
// 		}
// 	}
// 	if (!flag_exist)
// 		ft_putchar_fd('\n', cmd->fd);
// 	return (0);
// }
