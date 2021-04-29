/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:17:42 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/29 14:45:34 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	ft_redirect(char **arg, t_cmd *cmd)
{
	int	fd;

	if (ft_strncmp(arg[1], ">>", 2) == 0)
		fd = open(arg[2], O_CREAT | O_RDONLY | O_WRONLY | O_APPEND, 00777);
	else
		fd = open(arg[2], O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 00777);
	errno = 0;
	if (fd == -1)
	{
		print_error(errno);
		return (0);
	}
	else
		cmd->fd = fd;
	return (1);
}