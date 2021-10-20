/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:09:43 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/20 10:12:05 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtolower(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		(*str)[i] = ft_tolower((*str)[i]);
		i++;
	}
}