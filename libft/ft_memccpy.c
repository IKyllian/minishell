/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:20:19 by ctaleb            #+#    #+#             */
/*   Updated: 2020/11/25 16:28:19 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t size)
{
	unsigned int	i;
	unsigned char	*str_src;
	unsigned char	*str_dst;

	i = 0;
	str_src = (unsigned char *)src;
	str_dst = (unsigned char *)dst;
	while (i < size)
	{
		str_dst[i] = str_src[i];
		if (str_src[i] == (unsigned char)c)
			return (&str_dst[i + 1]);
		i++;
	}
	return (NULL);
}
