/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:45:05 by ctaleb            #+#    #+#             */
/*   Updated: 2020/11/23 17:03:19 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	int				i;
	unsigned char	*str_src;
	unsigned char	*str_dst;

	str_src = (unsigned char *)src;
	str_dst = (unsigned char *)dst;
	if (str_src > str_dst)
	{
		i = 0;
		while ((unsigned)i < size)
		{
			str_dst[i] = str_src[i];
			i++;
		}
	}
	else if (str_src < str_dst)
	{
		i = size - 1;
		while (i >= 0)
		{
			str_dst[i] = str_src[i];
			i--;
		}
	}
	return (dst);
}
