/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:08:18 by ctaleb            #+#    #+#             */
/*   Updated: 2020/11/24 10:25:16 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)ptr1;
	str2 = (unsigned char *)ptr2;
	while (i < size)
	{
		if (str1[i] == str2[i])
			i++;
		else
			return (str1[i] - str2[i]);
	}
	return (0);
}
