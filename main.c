/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/29 14:56:33 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

// void	check_cmd(char **arg, t_env *env, t_cmd *cmd)
// {
// 	if (ft_strncmp(arg[1], "<", 1) || ft_strncmp(arg[1], ">", 1)
// 		|| ft_strncmp(arg[1], ">>", 2) == 0)
// 		ft_redirect(arg, cmd);
// 	if (ft_strncmp(arg[0], "pwd", 3) == 0)
// 		cmd->exit_status = ft_pwd(cmd);
// 	else if (ft_strncmp(arg[0], "cd", 2) == 0)
// 		cmd->exit_status = ft_cd(*arg + 1, env);
// 	else if (ft_strncmp(arg[0], "echo", 4) == 0)
// 		cmd->exit_status = ft_echo(arg, env, cmd);
// 	else if (ft_strncmp(arg[0], "export", 6) == 0)
// 		cmd->exit_status = ft_export(env, cmd);
// 	else if (ft_strncmp(arg[0], "unset", 5) == 0)
// 		cmd->exit_status = ft_unset(env, arg);
// 	else if (ft_strncmp(arg[0], "env", 3) == 0)
// 		cmd->exit_status = ft_env(env, cmd);
//  else if (ft_strncmp(arg[0], "exit", 4) == 0)
// 	 	cmd->exit_status = ft_exit(env);
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
			ft_pwd(&cmd);
		else if (!strncmp(line, "export", 6))
			ft_export(env_s, &cmd);
		else if (!strncmp(line, "env", 3))
			ft_env(env_s, &cmd);
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
		if (cmd.fd != 1)
			cmd.fd = 1;
		ft_putstr_fd("minishell-0.1$ ", 1);
	}
	dbl_array_print(cmd.history);
	return (exit);
}

/* ----------------- Main de test avec line stocker dans un char** ----------------------- */
// int main(int argc, char **argv, char **env)
// {
// 	int		exit;
// 	char 	*line;
// 	t_cmd	cmd;
// 	t_env	*env_s;
// 	char	**arg;

// 	(void)argc;
// 	(void)argv;
// 	exit = 0;
// 	line = NULL;
// 	env_s = env_init(env);
// 	cmd = cmd_init();
// 	arg = malloc(sizeof(char *) * 4);
// 	ft_putstr_fd("minishell-0.1$ ", 1);
// 	while (ft_get_next_line(0, 5, &line))
// 	{
// 		history_save(&cmd, line);
// 		arg = ft_split(line, ' ');
// 		check_cmd(arg, env_s, &cmd);
// 		free(line);
// 		line = NULL;
// 		if (cmd.fd != 1)
// 		{
// 			close(cmd.fd);
// 			cmd.fd = 1;
// 		}
// 		ft_putstr_fd("minishell-0.1$ ", 1);
// 	}
// 	dbl_array_print(cmd.history);
// 	return (exit);
// }
