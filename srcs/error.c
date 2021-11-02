/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:35:08 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/02 08:47:12 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd.recount)
	{
		if (shell->cmd.redir[i].value)
			free(shell->cmd.redir[i].value);
		i++;
	}
	free(shell->cmd.redir);
	shell->cmd.redir = NULL;
	shell->cmd.recount = 0;
}

void	free_env_list_item(t_env *env)
{
	if (env->value)
		free(env->value);
	if (env->name)
		free(env->name);
	if (env)
		free(env);
	env = NULL;
}

void	lstclear_env(t_env **lst)
{
	t_env	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->name)
			free((*lst)->name);
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	free_tab(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
		free(tabl[i++]);
	free(tabl);
}

void	print_error(int errnum)
{
	ft_putstr_fd(strerror(errnum), 2);
	ft_putchar_fd('\n', 2);
	errno = 0;
}
