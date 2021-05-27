/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:05:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/27 10:41:45 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

char	*get_prompt_path(t_env *env)
{
	t_env	*env_pwd;
	char	*path;
	int		i;
	int 	size;
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
		while (env_pwd->value[++i])
			path[j++] = env_pwd->value[i];
		path[j] = '\0';
	}
	else
	{
		path = malloc(sizeof(char) * 2);
		path[0] = '~';
		path[1] = '\0';
	}
	return (path);
}

void	print_prompt(t_shell *shell)
{
	char	*path;

	path = get_prompt_path(shell->env);
	if (shell->cmd.exit_status == 0)
		ft_putstr_fd("\33[1;32m=>", 1);
	else
		ft_putstr_fd("\33[1;31m=>", 1);
	ft_putstr_fd("\33[1;36m minishell-0.1(", 1);
	ft_putstr_fd("\33[1;37m", 1);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\33[0;36m", 1);
	ft_putstr_fd(")$ ", 1);
	ft_putstr_fd("\33[0;37m", 1);
	if (path)
		free(path);
}