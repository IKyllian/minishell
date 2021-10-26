/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:57:48 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/26 08:00:29 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	validator(t_shell *shell)
{
	t_pars	*lst;

	lst = shell->cmd.parsed;
	if (lst && lst->type == 2)
		lst->type = 1;
	while (lst)
	{
		if (lst->type == 3)
		{
			if (lst->next && lst->next->type == 2)
				lst->next->type = 1;
			else if (lst->next && lst->next->type == 3)
			{
				printf("minishell: syntax error near unexpected token '|'\n");
				return (0);
			}
			else if (!lst->next)
			{
				printf("minishell: syntax error near unexpected token '|'\n");
				return (0);
			}
		}
		lst = lst->next;
	}
	return (1);
}
