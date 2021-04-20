/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:07:23 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/18 14:16:40 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*cpy;
	int		size;

	size = ft_strlen((char *)str) + 1;
	cpy = ft_calloc(size, sizeof(char));
	if (!cpy)
		return (NULL);
	ft_memcpy(cpy, str, size - 1);
	return (cpy);
}
