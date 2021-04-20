/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:12:43 by ctaleb            #+#    #+#             */
/*   Updated: 2020/11/26 15:59:54 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	unsigned int	i;
	unsigned int	src_size;

	if (!dst || !src)
		return (0);
	i = 0;
	src_size = ft_strlen((char *)src);
	if (dst_size == 0)
		return (src_size);
	while (src[i] && i < dst_size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dst_size != 0)
		dst[i] = '\0';
	return (src_size);
}
