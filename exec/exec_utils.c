/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 08:30:31 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/25 08:31:04 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	join_path(char **path_split, int i, struct dirent *pdirent, char **path)
{
	char	*temp;

	*path = path_split[i];
	temp = ft_strjoin(*path, "/");
	*path = ft_strjoin(temp, pdirent->d_name);
	if (temp)
		free(temp);
}