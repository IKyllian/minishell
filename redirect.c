/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:17:42 by kdelport          #+#    #+#             */
/*   Updated: 2021/06/29 15:46:13 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	restore_fd(t_shell *shell)
{
	if (dup2(shell->cmd.fd_stdin, shell->cmd.fd_in) == -1)
		print_error(errno);
	if (dup2(shell->cmd.fd_stdout, shell->cmd.fd_out) == -1)
		print_error(errno);
}

int	ft_redirect_in(t_cmd *cmd, t_pars **cmd_parsed)
{
	int	fd;

	if ((*cmd_parsed)->next)
		(*cmd_parsed) = (*cmd_parsed)->next;
	else
		return (0);
	fd = -1;
	close(cmd->fd_in);
	fd = open((*cmd_parsed)->value, O_CREAT | O_RDONLY, S_IRWXU);
	errno = 0;
	if (fd == -1)
	{
		print_error(errno);
		return (0);
	}
	if (dup2(fd, cmd->fd_in) == -1)
		print_error(errno);
	return (1);
}	

int	ft_redirect(t_cmd *cmd, char *redirect, t_pars **cmd_parsed)
{
	int	fd;

	if ((*cmd_parsed)->next)
		(*cmd_parsed) = (*cmd_parsed)->next;
	else
		return (0);
	fd = -1;
	close(cmd->fd_out);
	if (ft_strcmp(redirect, ">>") == 0)
		fd = open((*cmd_parsed)->value, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else if (ft_strcmp(redirect, ">") == 0)
		fd = open((*cmd_parsed)->value, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	errno = 0;
	if (fd == -1)
	{
		print_error(errno);
		return (0);
	}
	if (dup2(fd, cmd->fd_out) == -1)
		print_error(errno);
	return (1);
}

void ft_db_redirect_in(t_shell *shell, t_pars **cmd_parsed, t_pars *exit_word)
{
	t_pars	*args;
	int		ret;
	char	*line;
	t_pars *temp;

	if (!exit_word)
		ft_putstr_fd("Error : Pas de mot de sortie", shell->cmd.fd_out);
	ret = 1;
	args = lstnew_pars((*cmd_parsed)->value);
	(*cmd_parsed) = (*cmd_parsed)->next;
	while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
	{
		lstaddback_pars(&args, lstnew_pars((*cmd_parsed)->value));
		(*cmd_parsed) = (*cmd_parsed)->next;
	}
	while (ret)
	{
		ret = ft_get_next_line(0, 2, &line);
		if (ft_strcmp(line, exit_word->value) == 0)
			break ;
		lstaddback_pars(&args, lstnew_pars(line));
	}
	temp = args;
	check_cmd_arg(shell, &args);
}