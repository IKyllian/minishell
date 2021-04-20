/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:49:34 by ctaleb            #+#    #+#             */
/*   Updated: 2020/11/23 11:26:55 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t size)
{
	unsigned int	i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)ptr;
	while (i < size)
	{
		str[i] = (char)c;
		i++;
	}
	return (ptr);
}
