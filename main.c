/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/19 14:58:43 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	check_cmd_arg(t_shell *shell, t_pars **parsed)
{
	t_pars	*parsed_check;

	parsed_check = (*parsed);
	while (parsed_check && parsed_check->type != 3)
	{
		if (parsed_check->type == 4)
			ft_redirect(&shell->cmd, parsed_check->value, &parsed_check);
		parsed_check = parsed_check->next;
	}
	if (ft_strcmp((*parsed)->value, "pwd") == 0)
		shell->cmd.exit_status = ft_pwd(&shell->cmd, parsed);
	else if (ft_strcmp((*parsed)->value, "cd") == 0)
		shell->cmd.exit_status = ft_cd(shell, parsed);
	else if (ft_strcmp((*parsed)->value, "echo") == 0)
		shell->cmd.exit_status = ft_echo(shell, parsed);
	else if (ft_strcmp((*parsed)->value, "export") == 0)
		shell->cmd.exit_status = ft_export(shell, parsed);
	else if (ft_strcmp((*parsed)->value, "unset") == 0)
		shell->cmd.exit_status = ft_unset(shell, parsed);
	else if (ft_strcmp((*parsed)->value, "env") == 0)
		shell->cmd.exit_status = ft_env(shell, parsed);
	else if (ft_strcmp((*parsed)->value, "exit") == 0)
	 	shell->cmd.exit_status = ft_exit(shell, parsed);
	else
		ft_exec(shell, parsed);
}

void	exec_pipe(t_shell *shell, t_pars **parsed)
{
	pid_t	pid;
	int		pipefd[2];

	errno = 0;
	if (pipe(pipefd) == -1)
		print_error(errno);
	pid = fork();
	if (pid == -1)
		print_error(errno);
	else if (pid == 0)
	{
		if (dup2(pipefd[1], shell->cmd.fd_out) == -1)
			print_error(errno);
		close(pipefd[0]);
		check_cmd_arg(shell, parsed);
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		wait(NULL);
		if (dup2(pipefd[0], shell->cmd.fd_in) == -1)
			print_error(errno);
		close(pipefd[1]);
		while ((*parsed) && (*parsed)->type != 3)
			(*parsed) = (*parsed)->next;
		(*parsed) = (*parsed)->next;
		check_cmd_arg(shell, parsed);
		close(pipefd[0]);		
		if ((*parsed) && (*parsed)->type == 3)
			exec_pipe(shell, parsed);
	}
}

void	check_cmd(t_shell *shell)
{
	t_pars	*parsed;
	t_pars	*parsed_check;
	int		pipe_exist;

	parsed = shell->cmd.parsed;
	parsed_check = shell->cmd.parsed;
	pipe_exist = 0; 
	while (parsed)
	{
		while (parsed_check)
		{
			if (parsed_check->type == 3)
			{
				pipe_exist = 1;
				exec_pipe(shell, &parsed);
				break ;
			}
			parsed_check = parsed_check->next;
		}
		if (pipe_exist)
			break ;
		if (parsed->type == 3 || parsed->type == 4)
		{
			if (parsed->type == 4)
			{
				parsed = parsed->next;
				if (parsed)
					parsed = parsed->next;
			}
			else
				parsed = parsed->next;
			continue ;
		}
		check_cmd_arg(shell, &parsed);
	}
}

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
	print_prompt(&shell);
	while (ft_get_next_line(0, 5, &line))
	{
		arg = ft_split(line, ' ');
		init_pars(&shell.cmd, arg);
		check_cmd(&shell);
		free(line);
		line = NULL;
		restaure_fd(&shell);
		print_prompt(&shell);
	}
	// dbl_array_print(shell.cmd.history);
	return (exit);
}
