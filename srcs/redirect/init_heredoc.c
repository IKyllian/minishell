/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 08:42:46 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/02 08:48:24 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_file(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
}

void	exec_heredoc(t_shell *shell, t_pars *parse, int fd)
{
	char	*line;
	int		ret;
	int		i;

	i = 0;
	ret = 1;
	line = NULL;
	while (ret && g_heredoc)
	{
		ft_putstr_fd("> ", shell->cmd.fd_stdout);
		ret = ft_get_next_line(shell->cmd.fd_stdin, 2, &line);
		if (g_heredoc && ft_strcmp(line, parse->next->value) != 0)
			fill_file(line, fd);
		else
			break ;
		free(line);
		line = NULL;
	}
	if (line && g_heredoc)
	{
		free(line);
		line = NULL;
	}
}

void	launch_heredoc(t_pars *parse, t_shell *shell)
{
	int	fd;

	if (!parse->next || parse->next->type != 2)
	{
		ft_putstr_fd("minishell: syntax error ne", shell->cmd.fd_out);
		ft_putstr_fd("ar unexpected token\n", shell->cmd.fd_out);
		shell->cmd.hd_has_error = 1;
		g_heredoc = 0;
	}
	else
	{
		fd = open("heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
		exec_heredoc(shell, parse, fd);
		close(fd);
	}
}

void	init_heredoc(t_shell *shell, t_pars *parsed)
{
	struct sigaction	siga;
	t_pars				*parse;

	parse = parsed;
	sigemptyset(&siga.sa_mask);
	siga.sa_handler = sighandler;
	siga.sa_flags = 0;
	sigaction(SIGINT, &siga, NULL);
	g_heredoc = 1;
	while (parse && g_heredoc)
	{
		if (parse->type == 3 && shell->cmd.hd_has_error == 1)
			break ;
		if (parse->type == 4)
			launch_heredoc(parse, shell);
		parse = parse->next;
	}
}
