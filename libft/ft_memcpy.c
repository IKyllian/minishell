/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:54:00 by ctaleb            #+#    #+#             */
/*   Updated: 2020/11/28 15:39:41 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	unsigned int	i;
	unsigned char	*str_src;
	unsigned char	*str_dst;

	i = 0;
	if (!dst && !src)
		return (NULL);
	str_dst = (unsigned char *)dst;
	str_src = (unsigned char *)src;
	while (i < size)
	{
		str_dst[i] = str_src[i];
		i++;
	}
	return (dst);
}
