/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:00:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/14 08:35:10 by ctaleb           ###   ########lyon.fr   */
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

int	check_redirect(t_shell *shell, t_pars **parsed)
{
	t_pars	*parsed_check;
	int		ret;
	char	**exit_words;

	ret = 0;
	exit_words = NULL;
	parsed_check = (*parsed);
	while (parsed_check && parsed_check->type != 3)
	{
		if (parsed_check->type == 4)
		{
			if (ft_strcmp(parsed_check->value, "<") == 0)
				ft_redirect_in(&shell->cmd, &parsed_check);
			else if (ft_strcmp(parsed_check->value, "<<") == 0)
			{
				ret++;
				fill_exit_words(ret, &exit_words, parsed_check->next);
			}
			else
				ft_redirect(&shell->cmd, parsed_check->value, &parsed_check);
		}
		parsed_check = parsed_check->next;
	}
	if (ret)
	{
		if (ft_heredoc(shell, parsed, exit_words, ret) == 0)
			return (-1);
		return (0);
	}
	return (1);
}

int ft_redirect_(t_shell *shell, t_pars **parsed)
{
	int	ret;

	ret = check_redirect(shell, parsed);
	if (ret == -1)
		return (-1);
	else if (ret == 0)
		return (0);
	return (1);
}

int	cmd_to_exec(t_shell *shell, t_pars **parsed)
{
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

	parsed = shell->cmd.parsed;
	while (parsed)
	{
		if (parsed && parsed->type == 1
			&& check_pipe(&parsed, shell) == 0
			&& parsed->type == 1)
		{
			if (check_redirect(shell, &parsed) <= 0)
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
	// unset_term(&shell);
	return (exit);
}
