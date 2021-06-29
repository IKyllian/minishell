/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/06/29 15:28:33 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	check_cmd_arg(t_shell *shell, t_pars **parsed)
{
	t_pars	*parsed_check;

	parsed_check = (*parsed);
	while (parsed_check && parsed_check->type != 3 && parsed_check->type != 5)
	{
		if (parsed_check->type == 4)
		{
			if (ft_strcmp(parsed_check->value, "<") == 0)
				ft_redirect_in(&shell->cmd, &parsed_check);
			else if (ft_strcmp(parsed_check->value, "<<") == 0)
			{
				ft_db_redirect_in(shell, parsed, parsed_check->next);
				return ;
			}
			else
				ft_redirect(&shell->cmd, parsed_check->value, &parsed_check);
		}
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

void	check_cmd(t_shell *shell)
{
	t_pars	*parsed;
	t_pars	*parsed_check;

	parsed = shell->cmd.parsed;
	parsed_check = shell->cmd.parsed;
	while (parsed)
	{
		if (parsed && parsed->type == 1
			&& check_pipe(&parsed_check, &parsed, shell) == 0
			&& parsed->type == 1)
			check_cmd_arg(shell, &parsed);
		if (!parsed)
			break ;
		else if (parsed->type == 5)
		{
			restore_fd(shell);
			parsed = parsed->next;
		}
		else
			parsed = parsed->next;
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
		if (!quoting(&shell.cmd, line))
			continue ;
		history_save(&shell.cmd, line);
		tokenizer(&shell.cmd, line);
		// lstput_pars(shell.cmd.parsed);
		if (search_and_escape(&shell.cmd))
			check_cmd(&shell);
		else
			printf("Missing quotes\n");
		restore_fd(&shell);
		if (line)
			free(line);
		line = NULL;
		// lstput_pars(shell.cmd.parsed);
		lstclear_pars(&shell.cmd.parsed);
		print_prompt(&shell);
	}
	dbl_array_print(shell.cmd.history);
	// lstput_pars(shell.cmd.parsed);
	return (exit);
}
