/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:07:23 by ctaleb            #+#    #+#             */
/*   Updated: 2021/05/13 14:26:10 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*cpy;
	int		size;

	size = ft_strlen((char *)str) + 1;
	cpy = ft_calloc(size, sizeof(char));
	if (!cpy)
		return (NULL);
	if (ft_memcpy(cpy, str, size - 1) == NULL)
		return (NULL);
	return (cpy);
}
