/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/11 16:57:43 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

// void	check_cmd(char **arg, t_shell *shell)
// {
// 	if (arg[1] && (ft_strcmp(arg[1], "<") || ft_strcmp(arg[1], ">")
// 		|| ft_strcmp(arg[1], ">>") == 0))
// 		ft_redirect(arg, &shell->cmd);
// 	if (ft_strcmp(arg[0], "pwd") == 0)
// 		shell->cmd.exit_status = ft_pwd(&shell->cmd);
// 	else if (ft_strcmp(arg[0], "cd") == 0)
// 		shell->cmd.exit_status = ft_cd(*arg + 1, shell->env);
// 	else if (ft_strcmp(arg[0], "echo") == 0)
// 		shell->cmd.exit_status = ft_echo(arg, shell->env, &shell->cmd);
// 	else if (ft_strcmp(arg[0], "export") == 0)
// 		shell->cmd.exit_status = ft_export(shell);
// 	else if (ft_strcmp(arg[0], "unset") == 0)
// 		shell->cmd.exit_status = ft_unset(shell->env, arg);
// 	else if (ft_strcmp(arg[0], "env") == 0)
// 		shell->cmd.exit_status = ft_env(shell);
//  	else if (ft_strcmp(arg[0], "exit") == 0)
// 	 	cmd->exit_status = ft_exit(env, arg);
// 	else
// 		ft_exec(shell->env, arg);
// }

void	check_cmd_arg(t_shell *shell, t_pars **parsed)
{
	// else if (arg[1] && (ft_strcmp(arg[1], "<") || ft_strcmp(arg[1], ">")
		// 	|| ft_strcmp(arg[1], ">>") == 0))
		// 	ft_redirect(arg, &shell->cmd);
	if (ft_strcmp((*parsed)->value, "pwd") == 0)
		shell->cmd.exit_status = ft_pwd(&shell->cmd);
	else if (ft_strcmp((*parsed)->value, "cd") == 0)
		shell->cmd.exit_status = ft_cd(shell, parsed);
	else if (ft_strcmp((*parsed)->value, "echo") == 0)
		shell->cmd.exit_status = ft_echo(shell, parsed);
	else if (ft_strcmp((*parsed)->value, "export") == 0)
		shell->cmd.exit_status = ft_export(shell, parsed);
	else if (ft_strcmp((*parsed)->value, "unset") == 0)
		shell->cmd.exit_status = ft_unset(shell);
	else if (ft_strcmp((*parsed)->value, "env") == 0)
		shell->cmd.exit_status = ft_env(shell);
	// else if (ft_strcmp((*parsed)->value, "exit") == 0)
	//  	shell->cmd.exit_status = ft_exit(env, (*parsed)->value);
	else
		ft_exec(shell, parsed);
}

void	exec_pipe(t_shell *shell, t_pars **parsed)
{
	pid_t	pid;
	int		pipefd[2];
	// char	buff;
	
	errno = 0;
	if (pipe(pipefd) == -1)
		print_error(errno);
	pid = fork();
	if (pid == 0)
	{
		if (dup2(pipefd[1], shell->cmd.fd) == -1)
			print_error(errno);
		close(pipefd[0]);
		check_cmd_arg(shell, parsed);
		close(pipefd[1]);
	}
	else
	{
		wait(NULL);
		if (dup2(pipefd[0], shell->cmd.fd) == -1)
			print_error(errno);
		close(pipefd[1]);
		// while (read(pipefd[0], &buff, 1) > 0)
		// 	write(shell->cmd.fd, &buff, 1);
		check_cmd_arg(shell, parsed);
		close(pipefd[0]);		
		if (ft_strcmp((*parsed)->value, "|") == 0)
			exec_pipe(shell, parsed);
	}
}

void	check_cmd(t_shell *shell)
{
	t_pars	*parsed;

	parsed = shell->cmd.parsed; 
	while (parsed)
	{
		if (ft_strcmp(parsed->value, "|") == 0)
			exec_pipe(shell, &parsed);
		else
			check_cmd_arg(shell, &parsed);
		// parsed = (*parsed)->next;
	}
}

// int main(int argc, char **argv, char **env)
// {
// 	int		exit;
// 	char 	*line;
// 	t_shell	shell;

// 	(void)argc;
// 	(void)argv;
// 	exit = 0;
// 	line = NULL;
// 	shell = shell_init(env);
// 	ft_putstr_fd("minishell-0.1$ ", 1);
// 	while (ft_get_next_line(0, 5, &line))
// 	{
// 		printf("TEST\n");
// 		if (!quoting(&shell.cmd, line))
// 			continue ;
// 		history_save(&shell.cmd);
// 		if (!ft_strcmp(line, "pwd"))
// 			ft_pwd(&shell.cmd);
// 		// else if (!ft_strcmp(line, "export"))
// 		// 	ft_export(&shell);
// 		// else if (!ft_strcmp(line, "env"))
// 		// 	ft_env(&shell);
// 		// else if (!ft_strcmp(line, "exit"))
// 		// {
// 		// 	exit = 0;
// 		// 	break ;
// 		// }
// 		// else
// 		// 	ft_cd(line, &shell);
// 			// ft_echo(line);
// 		free(line);
// 		line = NULL;
// 		if (shell.cmd.fd != 1)
// 			shell.cmd.fd = 1;
// 		ft_putstr_fd("minishell-0.1$ ", 1);
// 	}
// 	dbl_array_print(shell.cmd.history);
// 	return (exit);
// }

/* ----------------- Main de test avec Liste ----------------------- */
int main(int argc, char **argv, char **env)
{
	int		exit;
	char 	*line;
	t_shell	shell;
	char	**arg;

	(void)argc;
	(void)argv;
	exit = 0;
	line = NULL;
	shell = shell_init(env);
	arg = malloc(sizeof(char *) * 4);
	ft_putstr_fd("minishell-0.1$ ", 1);
	while (ft_get_next_line(0, 5, &line))
	{
		arg = ft_split(line, ' ');
		init_pars(&shell.cmd, arg);
		check_cmd(&shell);
		free(line);
		line = NULL;
		if (shell.cmd.fd != 1)
			shell.cmd.fd = 1;
		ft_putstr_fd("minishell-0.1$ ", 1);
	}
	// dbl_array_print(shell.cmd.history);
	return (exit);
}
