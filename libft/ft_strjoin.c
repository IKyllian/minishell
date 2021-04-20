/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:54:06 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/19 14:46:40 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = ft_calloc(size, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcat(str, s1, size);
	ft_strlcat(str, s2, size);
	return (str);
}
