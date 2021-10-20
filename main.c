/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/20 10:54:27 by ctaleb           ###   ########lyon.fr   */
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
	if (*exit_words != NULL)
		free(*exit_words);
	*exit_words = temp;
}


int check_heredoc(t_shell *shell, t_pars **parsed)
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
		{
			if (ft_strcmp(parsed_check->value, "<<") == 0)
			{
				heredoc++;
				fill_exit_words(heredoc, &exit_words, parsed_check->next);
			}
		}
		parsed_check = parsed_check->next;
	}
	if (heredoc)
		return(ft_heredoc(shell, parsed, exit_words, heredoc));
	return (1);
}

int	check_redirect(t_shell *shell, t_pars **parsed, int index_cmd)
{
	int		first_index;

	first_index = 0;
	while (shell->cmd.redir[shell->cmd.i_redir].value != NULL
		&& shell->cmd.redir[shell->cmd.i_redir].pipe_index <= index_cmd)
	{
		if (shell->cmd.redir[shell->cmd.i_redir].pipe_index == index_cmd)
		{
			if (shell->cmd.redir[shell->cmd.i_redir].type == 1)
				ft_redirect_in(&shell->cmd, shell->cmd.redir[shell->cmd.i_redir]);
			else
				ft_redirect(&shell->cmd, shell->cmd.redir[shell->cmd.i_redir]);
		}
		shell->cmd.i_redir++;
	}
	return (check_heredoc(shell, parsed));
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

void	check_cmd(t_shell *shell)
{
	t_pars	*parsed;

	parsed = shell->cmd.parsed;
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
