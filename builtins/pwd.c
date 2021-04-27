/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:43 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/23 16:58:22 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_pwd(void)
{
	char	path[PATH_MAX];

	errno = 0;
	if (getcwd(path, PATH_MAX))
		ft_putstr_fd(path, 1);
	else
	{
		print_error(errno);
		return (1);
	}
	ft_putchar_fd('\n', 1);
	return (0);
}