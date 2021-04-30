/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:15:58 by ctaleb            #+#    #+#             */
/*   Updated: 2021/04/30 15:18:52 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, int len)
{
	char	*cpy;
	int		size;

	size = ft_strlen((char *)str);
	if (size < len)
		len = size;
	cpy = ft_calloc(len + 1, sizeof(char));
	if (!cpy)
		return (NULL);
	ft_memcpy(cpy, str, len);
	return (cpy);
}