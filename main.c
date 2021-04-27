/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/23 15:37:08 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

// void	check_cmd(char **arg, t_env *env, t_cmd *cmd)
// {
// 	if (arg[0] == "pwd")
// 		cmd->exit_status = ft_pwd();
// 	else if (arg[0] == "cd")
// 		cmd->exit_status = ft_cd(arg, env);
// 	else if (arg[0] == "echo")
// 		cmd->exit_status = ft_echo(arg);
// 	else if (arg[0] == "export")
// 		cmd->exit_status = ft_export(env);
// 	else if (arg[0] == "unset")
// 		cmd->exit_status = ft_unset(env, arg);
// 	else if (arg[0] == "env")
// 		cmd->exit_status = ft_env(env);
// 	else if (arg[0] == "exit")
// 		cmd->exit_status = ft_exit(env);
// }

int main(int argc, char **argv, char **env)
{
	int		exit;
	char 	*line;
	t_cmd	cmd;
	t_env	*env_s;

	(void)argc;
	(void)argv;
	exit = 0;
	line = NULL;
	env_s = env_init(env);
	cmd = cmd_init();
	ft_putstr_fd("minishell-0.1$ ", 1);
	while (ft_get_next_line(0, 5, &line))
	{
		history_save(&cmd, line);	
		if (!strncmp(line, "pwd", 3))
			ft_pwd();
		else if (!strncmp(line, "export", 6))
			ft_export(env_s);
		else if (!strncmp(line, "env", 3))
			ft_env(env_s);
		else if (!strncmp(line, "exit", 5))
		{
			exit = 0;
			break ;
		}
		else
			ft_cd(line, env_s);
			// ft_echo(line);
		free(line);
		line = NULL;
		ft_putstr_fd("minishell-0.1$ ", 1);
	}
	dbl_array_print(cmd.history);
	return (exit);
}
