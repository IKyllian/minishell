/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:57:13 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/19 14:46:24 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	ft_lstsize_pars(t_pars *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_pars	*ft_lstnew_pars(int type, char *value)
{
	t_pars	*pars;

	pars = ft_calloc(1, sizeof(t_pars));
	if (!pars)
		return (NULL);
	pars->type = type;
	pars->value = value;
	pars->next = NULL;
	return (pars);
}

t_pars	*ft_lstlast_pars(t_pars *lst)
{
	int	i;
	int	max;

	i = 0;
	max = ft_lstsize_pars(lst);
	while (i < max - 1)
	{
		i++;
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_pars(t_pars **alst, t_pars *new)
{
	t_pars	*tmp;

	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = ft_lstlast_pars(*alst);
	tmp->next = new;
}

// 1 = Commande / 2 = Argument / 3 = Pipe
void	init_pars(t_cmd *cmd, char **arg)
{
	int i;
	t_pars *cmd_parsed;
	int type;

	i = 0;
	cmd_parsed = NULL;
	while (arg[i])
	{
		if (i == 0 )//|| i == 3)
			type = 1;
		else if (ft_strcmp(arg[i], "<") == 0 || ft_strcmp(arg[i], ">>") == 0 || ft_strcmp(arg[i], ">") == 0)
			type = 4;
		else if (ft_strcmp(arg[i], "|") == 0)
			type = 3;
		else
			type = 2;
		ft_lstadd_back_pars(&cmd_parsed, ft_lstnew_pars(type, arg[i]));
		i++;	
	}
	cmd->parsed = cmd_parsed;
}
