/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:41:17 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/19 14:47:31 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcount(const char *str, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			n++;
			while (str[i] != c && str[i])
				i++;
		}
		while (str[i] == c && str[i])
			i++;
	}
	return (n);
}

static void	ft_fillup(const char *str, char c, char **split)
{
	int				n;
	unsigned int	i;
	unsigned int	start;

	i = 0;
	n = -1;
	while (str[i])
	{
		if (str[i] != c)
		{
			n++;
			start = i;
			while (str[i] != c && str[i])
				i++;
			split[n] = ft_substr(str, start, i - start);
		}
		while (str[i] == c && str[i])
			i++;
	}
}

static int	ft_freeall(char **split, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (!split[i])
		{
			i = 0;
			while (i < n)
			{
				if (split[i])
					free(split[i]);
				i++;
			}
			free(split);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		n;
	char	**split;

	if (!s)
		return (NULL);
	n = ft_strcount(s, c) + 1;
	split = ft_calloc(n, sizeof(char *));
	if (!split)
		return (NULL);
	split[n - 1] = NULL;
	if (ft_strchr(s, c) == NULL)
	{
		if (!ft_strlen(s))
			split[0] = NULL;
		else
			split[0] = ft_strdup(s);
		if (ft_freeall(split, n - 1))
			return (NULL);
		return (split);
	}
	ft_fillup(s, c, split);
	if (ft_freeall(split, n - 1))
		return (NULL);
	return (split);
}
