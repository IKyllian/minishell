/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:54:06 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/19 15:00:44 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chrrjoin(char const *s1, char const c)
{
	int		size;
	char	*str;

	if (!s1 || !c)
		return (NULL);
	size = ft_strlen((char *)s1) + 2;
	str = ft_calloc(size, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = c;
	ft_strlcat(str, s1, size);
	return (str);
}
