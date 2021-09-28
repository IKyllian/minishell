/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/09/28 16:35:58 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	check_redirect(t_shell *shell, t_pars **parsed)
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
				if (ft_db_redirect_in(shell, parsed, parsed_check->next) == 0)
					return (-1);
			}
			else
				ft_redirect(&shell->cmd, parsed_check->value, &parsed_check);
		}
		parsed_check = parsed_check->next;
	}
	return (1);
}

int	check_cmd_arg(t_shell *shell, t_pars **parsed)
{
	int ret;

	ret = check_redirect(shell, parsed);
	if (ret == -1)
		return (-1);
	else if (ret == 0)
		return (0);
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
	return (1);
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
			if (check_cmd_arg(shell, &parsed) == -1)
				break;
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

void	new_prompt()
{
	ft_putstr_fd("\n", 0);
	ft_putstr_fd("minishell\n", 0);
	signal(SIGINT, new_prompt);
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
	signal(SIGINT, new_prompt);
	// signal(SIGQUIT, new_prompt); "CTRL \" \*
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
