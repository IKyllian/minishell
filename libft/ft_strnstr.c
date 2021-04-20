/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:56:15 by ctaleb            #+#    #+#             */
/*   Updated: 2020/11/25 16:39:22 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hst, const char *ndl, size_t size)
{
	unsigned int	ndl_len;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	ndl_len = ft_strlen((char *)ndl);
	if (ndl_len == 0)
		return ((char *)hst);
	while (hst[i] && i < size)
	{
		j = 0;
		while (hst[i + j] == ndl[j])
		{
			j++;
			if ((i + j) > size)
				return (NULL);
			if (j == ndl_len)
				return ((char *)hst + i);
		}
		i++;
	}
	return (NULL);
}
