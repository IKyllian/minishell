/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:10:37 by ctaleb            #+#    #+#             */
/*   Updated: 2020/11/25 11:32:40 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int c, size_t size)
{
	unsigned int	i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)ptr;
	while (i < size)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
