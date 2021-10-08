/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:17:42 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/08 13:46:14 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void    restore_fd(t_shell *shell)
{
    if (dup2(shell->cmd.fd_stdin, shell->cmd.fd_in) == -1)
        print_error(errno);
    if (dup2(shell->cmd.fd_stdout, shell->cmd.fd_out) == -1)
        print_error(errno);
    shell->cmd.is_heredoc = 0;
}

int    ft_redirect_in(t_cmd *cmd, t_pars **cmd_parsed)
{
    int    fd;

    if ((*cmd_parsed)->next)
        (*cmd_parsed) = (*cmd_parsed)->next;
    else
        return (0);
    fd = -1;
    close(cmd->fd_in);
    fd = open((*cmd_parsed)->value, O_RDONLY, S_IRWXU);
    errno = 0;
    if (fd == -1)
    {
        // print_error(errno);
        return (0);
    }
    if (dup2(fd, cmd->fd_in) == -1)
        print_error(errno);
    return (1);
}    

int    ft_redirect(t_cmd *cmd, char *redirect, t_pars **cmd_parsed)
{
    int    fd;

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

int    ft_heredoc(t_shell *shell, t_pars **cmd_parsed,
        char **exit_words, int size)
{
    t_pars	*args;
    int		ret;
    char	*line;
    int		fd;
    int		i;

    if (!exit_words[size - 1])
    {
        ft_putstr_fd("Error : No exit word\n", shell->cmd.fd_out);
        return (0);
    }
    i = 0;
    ret = 1;
    line = NULL;
    shell->cmd.is_heredoc = 1;
    fd = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0777);
    args = lstnew_pars((*cmd_parsed)->value);
    (*cmd_parsed) = (*cmd_parsed)->next;
    while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
    {
        lstaddback_pars(&args, lstnew_pars((*cmd_parsed)->value));
        (*cmd_parsed) = (*cmd_parsed)->next;
    }
    while (ret)
    {
        ft_putstr_fd("> ", shell->cmd.fd_stdout);
        ret = ft_get_next_line(shell->cmd.fd_in, 2, &line);
        if (i == size - 1 && ft_strcmp(line, exit_words[i]) != 0)
        {
            ft_putstr_fd(line, fd);
            ft_putstr_fd("\n", fd);
        }
        if (ft_strcmp(line, exit_words[i]) == 0)
        {
            if (i++ == size - 1)
                break ;
        }
    }
	cmd_to_exec(shell, &args);
	close(fd);
    return (1);
}