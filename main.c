/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/30 11:10:52 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	cmd_to_exec(t_shell *shell, t_pars **parsed)
{
	if ((*parsed)->type == 5)
	{
		ft_exec(shell, parsed, 1);
		return (0);
	}
	ft_strtolower(&(*parsed)->value);
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
	else if (ft_strcmp((*parsed)->value, "exit") == 0 && !shell->cmd.is_pipe)
		ft_exit(shell, parsed);
	else if (ft_strcmp((*parsed)->value, "exit") == 0 && shell->cmd.is_pipe)
		ft_exit_pipe(shell, parsed);
	else
		ft_exec(shell, parsed, 0);
	return (1);
}

void	check_cmd(t_shell *shell)
{
	t_pars	*parsed;

	parsed = shell->cmd.parsed;
	init_heredoc(shell, shell->cmd.parsed);
	if (!g_heredoc)
		return ;
	while (parsed)
	{
		if (parsed
			&& (parsed->type == 1 || parsed->type == 5 || parsed->type == 4))
		{
			if (check_pipe(&parsed, shell) == 1)
				break ;
		}
		if ((parsed->type == 1 || parsed->type == 5 || parsed->type == 4))
		{
			if (check_redirect(shell, &parsed, 0) <= 0)
				break ;
			cmd_to_exec(shell, &parsed);
		}
		if (!parsed)
			break ;
		parsed = parsed->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	int		exit;
	t_shell	shell;

	(void)argc;
	(void)argv;
	exit = 0;
	shell = shell_init(env);
	prompt(&shell);
	unset_term(&shell);
	return (exit);
}
