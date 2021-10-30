/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strct_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:02:29 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/30 08:38:33 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_shell	shell_init(char **env)
{
	t_shell	shell;

	shell.env = env_init(env);
	shell.cmd = cmd_init();
	tcgetattr(0, &shell.saved_term);
	return (shell);
}

t_cmd	cmd_init(void)
{
	t_cmd	cmd;

	cmd.history = NULL;
	cmd.parsed = NULL;
	cmd.exit_status = 0;
	cmd.line = NULL;
	cmd.prompt = NULL;
	cmd.fd_stdout = dup(1);
	cmd.fd_stdin = dup(0);
	cmd.fd_out = 1;
	cmd.fd_in = 0;
	cmd.squote = 0;
	cmd.dquote = 0;
	cmd.is_heredoc = 0;
	cmd.hd_has_error = 0;
	cmd.i_pids = 0;
	cmd.i_redir = 0;
	cmd.index_pipe = 0;
	cmd.redir = NULL;
	cmd.set_old_to_null = 0;
	cmd.nbr_pipe = 0;
	cmd.mode_export = 0;
	cmd.pids = ft_calloc(1, sizeof(t_pids));
	return (cmd);
}

void	get_env_value(char **value, int len, int i, char *line)
{
	int	j;

	j = 0;
	while (line[len - i] && i >= 0)
		(*value)[j++] = line[len - i--];
	(*value)[j] = '\0';
}

void	get_env_var(char *line, char **lst_name, char **lst_value)
{
	int		i;
	int		j;
	int		len;
	char	*name;
	char	*value;

	i = 0;
	j = -1;
	len = 0;
	while (line[len] && line[len] != '=')
		len++;
	name = malloc(sizeof(char) * (len + 1));
	mem_check(name);
	while (line[++j] && line[j] != '=')
		name[j] = line[j];
	name[j] = '\0';
	while (line[++len])
		i++;
	value = malloc(sizeof(char) * (i + 1));
	mem_check(value);
	get_env_value(&value, len, i, line);
	*lst_name = name;
	*lst_value = value;
}

t_env	*env_init(char **env_tab)
{
	int		i;
	t_env	*env;
	char	*name;
	char	*value;

	i = -1;
	env = NULL;
	while (env_tab[++i])
	{
		get_env_var(env_tab[i], &name, &value);
		if (ft_strcmp(name, "OLDPWD") == 0)
		{
			ft_lstadd_back_env(&env, ft_lstnew_env(name, ft_strdup("\0")));
			if (value)
				free(value);
		}
		else
			ft_lstadd_back_env(&env, ft_lstnew_env(name, value));
	}
	return (env);
}
