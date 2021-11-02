/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:52:40 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/02 08:48:24 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*cpy_env_list(t_env *env)
{
	t_env	*cpy_env;

	cpy_env = NULL;
	while (env)
	{
		if (env->value != NULL)
			ft_lstadd_back_env(&cpy_env, ft_lstnew_env(ft_strdup(env->name), \
				ft_strdup(env->value)));
		else
			ft_lstadd_back_env(&cpy_env, ft_lstnew_env(ft_strdup(env->name), \
				NULL));
		env = env->next;
	}
	return (cpy_env);
}

void	print_env_line(t_env *env, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(env->name, fd);
	if (env->value != NULL)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(env->value, fd);
		ft_putchar_fd('\"', fd);
	}
	ft_putchar_fd('\n', fd);
}

void	sort_env(t_env *env_cpy, t_env *first)
{
	char	*name_temp;
	char	*value_temp;
	int		is_sort;

	is_sort = 0;
	while (!is_sort)
	{
		is_sort = 1;
		env_cpy = first;
		while (env_cpy)
		{
			if (env_cpy->next
				&& ft_strcmp(env_cpy->name, env_cpy->next->name) > 0)
			{
				name_temp = env_cpy->name;
				value_temp = env_cpy->value;
				env_cpy->name = env_cpy->next->name;
				env_cpy->value = env_cpy->next->value;
				env_cpy->next->name = name_temp;
				env_cpy->next->value = value_temp;
				is_sort = 0;
			}
			env_cpy = env_cpy->next;
		}
	}
}

void	sort_and_print_env(t_shell *shell)
{
	t_env	*env_cpy;
	t_env	*first;

	env_cpy = cpy_env_list(shell->env);
	first = env_cpy;
	sort_env(env_cpy, first);
	while (first)
	{
		print_env_line(first, shell->cmd.fd_out);
		first = first->next;
	}
	lstclear_env(&env_cpy);
}

int	is_valide_character(char c, char *cmd_value, int indx, t_shell *shell)
{
	if (((c >= 48 && c <= 57) || c == '=' || c == '+') && indx == 0)
		return (0);
	if (c == '+' && cmd_value[indx + 1] && cmd_value[indx + 1] == '=')
	{
		shell->cmd.mode_export = 1;
		return (1);
	}
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122) || (c == '_'))
		return (1);
	return (0);
}
