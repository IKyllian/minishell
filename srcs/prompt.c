/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:05:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/03 08:15:28 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt_path(t_env *env, t_shell *shell)
{
	t_env	*env_pwd;
	char	*path;
	int		i;
	int		size;
	int		j;

	env_pwd = srch_and_return_env_var(env, "PWD");
	if (!env_pwd || !env_pwd->value)
		return (NULL);
	i = ft_strlen(env_pwd->value) - 1;
	size = ft_strlen(env_pwd->value) - 1;
	j = 0;
	if (env_pwd->value[i] != '/')
	{
		while (env_pwd->value[i] && env_pwd->value[i] != '/')
			i--;
		path = malloc(sizeof(char) * ((size - i) + 1));
		mem_check(shell, path);
		while (env_pwd->value[++i])
			path[j++] = env_pwd->value[i];
		path[j] = '\0';
	}
	else
		return (pather(shell));
	return (path);
}

void	set_prompt(t_shell *shell, char **prompt)
{
	char	*path;
	char	*prefix;
	char	*suffix;
	char	*temp;

	path = get_prompt_path(shell->env, shell);
	if (*prompt)
		free(*prompt);
	if (shell->cmd.exit_status == 0)
		prefix = "\33[1;32m=>\33[1;36m minishell-1.0(\33[1;37m";
	else
		prefix = "\33[1;31m=>\33[1;36m minishell-1.0(\33[1;37m";
	suffix = "\33[1;36m)$ \33[0;37m";
	*prompt = ft_strjoin("", prefix);
	if (!path)
		temp = ft_strjoin(*prompt, "null");
	else
		temp = ft_strjoin(*prompt, path);
	free(*prompt);
	*prompt = ft_strjoin(temp, suffix);
	free(temp);
	if (path)
		free(path);
	return ;
}

void	deep_parser(t_shell *shell)
{
	history_save(&shell->cmd, shell->line, shell);
	tokenizer(&shell->cmd, shell->line, shell);
	search_and_sub(shell);
	if (search_and_escape(&shell->cmd) && redirect(&shell->cmd, shell))
		if (validator(shell))
			check_cmd(shell);
}

int	prompt(t_shell *shell)
{
	shell->line = "";
	while (shell->line)
	{
		g_heredoc = 0;
		set_term(shell);
		set_prompt(shell, &shell->cmd.prompt);
		signal(SIGINT, m_sigkill);
		shell->line = readline(shell->cmd.prompt);
		if (!shell->line)
		{
			ft_exit(shell, &shell->cmd.parsed);
			break ;
		}
		if (!quoting(&shell->cmd, shell->line))
			continue ;
		if (g_heredoc)
			shell->cmd.exit_status = 1;
		deep_parser(shell);
		restore_cmd(shell);
	}
	return (0);
}
