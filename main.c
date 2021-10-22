/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/22 13:50:40 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	fill_exit_words(int size, char ***exit_words, t_pars *new_exit_word)
{
	char	**temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(char *) * (size + 1));
	if (size > 1)
	{
		while (i < size - 1)
		{
			temp[i] = (*exit_words)[i];
			i++;
		}
	}
	if (new_exit_word)
		temp[i++] = new_exit_word->value;
	else
		temp[i++] = NULL;
	temp[i] = NULL;
	// if (*exit_words != NULL)
	// 	free(*exit_words);
	*exit_words = temp;
}

int check_heredoc(t_shell *shell, t_pars **parsed, int ret)
{
	t_pars	*parsed_check;
	int		heredoc;
	char	**exit_words;

	parsed_check = (*parsed);
	heredoc = 0;
	exit_words = NULL;
	while (parsed_check && parsed_check->type != 3)
	{
		if (parsed_check->type == 4)
				heredoc++;
		parsed_check = parsed_check->next;
	}
	if (heredoc && ret > 0)
		return(ft_heredoc(shell, parsed));
	return (ret);
}

int	check_redirect(t_shell *shell, t_pars **parsed, int index_cmd)
{
	int	first_index;
	int	ret;

	first_index = 0;
	ret = 1;
	while (shell->cmd.redir[shell->cmd.i_redir].value != NULL
		&& shell->cmd.redir[shell->cmd.i_redir].pipe_index <= index_cmd)
	{
		if (shell->cmd.redir[shell->cmd.i_redir].pipe_index == index_cmd)
		{
			if (shell->cmd.redir[shell->cmd.i_redir].type == 1)
				ret = ft_redirect_in(&shell->cmd, shell->cmd.redir[shell->cmd.i_redir]);
			else
				ret = ft_redirect(&shell->cmd, shell->cmd.redir[shell->cmd.i_redir]);
		}
		shell->cmd.i_redir++;
	}
	return (check_heredoc(shell, parsed, ret));
}

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
	else if (ft_strcmp((*parsed)->value, "exit") == 0)
		shell->cmd.exit_status = ft_exit(shell, parsed);
	else
		ft_exec(shell, parsed, 0);
	return (1);
}

void	exec_heredoc(t_shell *shell,  t_pars *parse, int fd)
{
	char	*line;
	int		ret;
	int		i;

	i = 0;
	ret = 1;
	line = NULL;
	g_heredoc = 1;
	while (ret && g_heredoc)
	{
		ft_putstr_fd("> ", shell->cmd.fd_stdout);
		ret = ft_get_next_line(shell->cmd.fd_stdin, 2, &line);
		if (ft_strcmp(line, parse->next->value) != 0)
		{
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
		}
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

void	init_heredoc(t_shell *shell, t_pars *parsed)
{
	t_pars *parse;
	int		fd;

	parse = parsed;
	while (parse)
	{
		if (parse->type == 3 && shell->cmd.hd_has_error == 1)
			break ;
		if (parse->type == 4)
		{
			if (!parse->next)
			{
				ft_putstr_fd("Syntax error near unexpected token\n", shell->cmd.fd_out);
				shell->cmd.hd_has_error = 1;
			}
			else
			{
				fd = open("heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
				exec_heredoc(shell, parse, fd);
				close(fd);
			}
		}
		parse = parse->next;
	}
}

void	check_cmd(t_shell *shell)
{
	t_pars	*parsed;

	parsed = shell->cmd.parsed;
	init_heredoc(shell, shell->cmd.parsed);
	while (parsed)
	{
		if (parsed && (parsed->type == 1 | parsed->type == 5 | parsed->type == 4))
		{
			if (check_pipe(&parsed, shell) == 1)
				break;
		}
		if ((parsed->type == 1 | parsed->type == 5 | parsed->type == 4))
		{
			if (check_redirect(shell, &parsed, 0) <= 0)
				break ;
			g_pids.mode = 1;
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
