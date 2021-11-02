/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 08:28:27 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/02 08:48:24 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc(t_shell *shell, t_pars **parsed, int ret)
{
	t_pars	*parsed_check;
	int		heredoc;

	parsed_check = (*parsed);
	heredoc = 0;
	while (parsed_check && parsed_check->type != 3)
	{
		if (parsed_check->type == 4)
			heredoc++;
		parsed_check = parsed_check->next;
	}
	if (heredoc && ret > 0)
		return (ft_heredoc(shell, parsed));
	return (ret);
}

int	is_last_heredoc(t_shell *shell)
{
	int	i;

	i = 0;
	while (i <= shell->cmd.pids->count)
	{
		if (i > shell->cmd.index_pipe)
		{
			if (shell->cmd.pids->pid[i].is_heredoc == 1)
				return (0);
		}
		i++;
	}
	return (1);
}

void	fill_arg_hd(t_pars **cmd_parsed, t_pars	**args, int *cmd_exit, \
	t_pars **first)
{
	if ((*cmd_parsed)->type == 1)
	{
		*cmd_exit = 1;
		*args = lstnew_pars(ft_strdup((*cmd_parsed)->value));
		*first = *args;
		(*cmd_parsed) = (*cmd_parsed)->next;
		while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
		{
			lstaddback_pars(args, lstnew_pars(ft_strdup((*cmd_parsed)->value)));
			(*cmd_parsed) = (*cmd_parsed)->next;
		}
		if (ft_strcmp((*first)->value, "echo") == 0)
		{
			(*cmd_parsed) = (*cmd_parsed)->next;
			(*cmd_parsed) = (*cmd_parsed)->next;
			while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
			{
				lstaddback_pars(args, \
					lstnew_pars(ft_strdup((*cmd_parsed)->value)));
				(*cmd_parsed) = (*cmd_parsed)->next;
			}
		}
	}
}

int	ft_heredoc(t_shell *shell, t_pars **cmd_parsed)
{
	t_pars	*args;
	int		fd;
	int		command_exist;
	t_pars	*first;

	command_exist = 0;
	if (shell->cmd.hd_has_error)
		return (-1);
	else if (!is_last_heredoc(shell))
		return (0);
	shell->cmd.is_heredoc = 1;
	fill_arg_hd(cmd_parsed, &args, &command_exist, &first);
	fd = open("heredoc.txt", O_RDWR, 0777);
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	if (command_exist)
	{
		cmd_to_exec(shell, &args);
		args = first;
		lstclear_pars(&args);
	}
	close(STDIN_FILENO);
	close(fd);
	unlink("heredoc.txt");
	return (0);
}
