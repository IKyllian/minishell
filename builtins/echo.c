/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:31 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/11 16:51:39 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	ft_echo(char *str)
// {
// 	char *env_var;
// 	int	flag_exist;

// 	flag_exist = 0;
// 	if (str)
// 	{
// 		if (str[0] != '$')
// 			ft_putstr_fd(str, 1);
// 		else
// 		{
// 			if (str[1] == ' ')
// 				ft_putstr_fd(str, 1);
// 			else
// 			{
// 				env_var = getenv(str + 1);
// 				if (env_var != NULL)
// 					ft_putstr_fd(env_var, 1);
// 			}
// 		} 
// 	}
// 	if (!flag_exist)
// 		ft_putchar_fd('\n', 1);
// 	return (1);
// }

//Exit status = 0 if no error
int	ft_echo(t_shell *shell, t_pars **cmd_parsed)
{
	int		i;
	int		flag_exist;

	if ((*cmd_parsed)->next != NULL)
		(*cmd_parsed) = (*cmd_parsed)->next;
	flag_exist = 0;
	i = 0;
	while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
	{
		if (i == 1 && ft_strcmp((*cmd_parsed)->value, "-n") == 0)
			flag_exist = 1;
		if ((*cmd_parsed)->value[0] == '$' && (*cmd_parsed)->value[1] != ' ')
			srch_and_dislay_env_var(shell->env, (*cmd_parsed)->value + 1);// +1 pour skip le $
		else if ((*cmd_parsed)->value[0] == '$' && (*cmd_parsed)->value[1] == '?')
			ft_putnbr_fd(shell->cmd.exit_status, shell->cmd.fd);
		else
			ft_putstr_fd((*cmd_parsed)->value, shell->cmd.fd);
		ft_putchar_fd(' ', shell->cmd.fd);
		(*cmd_parsed) = (*cmd_parsed)->next;
		i++;
	}
	if (!flag_exist)
		ft_putchar_fd('\n', shell->cmd.fd);
	shell->cmd.exit_status = 0;
	return (0);
}
