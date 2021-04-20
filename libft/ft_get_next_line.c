/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:16:07 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/19 14:58:36 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_line(char *temp)
{
	int		i;
	int		j;
	char	*nline;

	i = 0;
	while (temp[i] != '\n' && temp[i])
		i++;
	nline = ft_calloc(i + 1, sizeof(char));
	if (!nline)
		return (NULL);
	j = 0;
	while (j < i)
	{
		nline[j] = temp[j];
		j++;
	}
	return (nline);
}

static char	*trim_temp(char *temp)
{
	int				i;
	int				j;
	char			*new_temp;
	unsigned int	new_size;

	i = 0;
	while (temp[i] != '\n' && temp[i])
		i++;
	i++;
	new_size = ft_strlen(&temp[i]);
	new_temp = ft_calloc(new_size + 1, sizeof(char));
	if (!new_temp)
	{
		if (temp)
			free(temp);
		return (NULL);
	}
	j = 0;
	while (temp[i])
		new_temp[j++] = temp[i++];
	free(temp);
	return (new_temp);
}

static int	liberator(char **str, int rd)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
	return (rd);
}

static char	*joiner(char *temp, char *buf, int buf_len)
{
	char			*joined;
	unsigned int	new_size;

	new_size = ft_strlen(temp) + buf_len + 2;
	joined = ft_calloc(new_size, sizeof(char));
	if (!joined)
	{
		if (temp)
			free(temp);
		return (NULL);
	}
	ft_strlcat(joined, temp, new_size);
	if (temp)
		free(temp);
	ft_strlcat(joined, buf, new_size);
	return (joined);
}

int	ft_get_next_line(int fd, int b_size, char **line)
{
	static char	*temp;
	char		*buf;
	int			rd;

	rd = 1;
	if (b_size <= 0)
		return (-1);
	if (!temp)
		temp = ft_calloc(1, sizeof(char));
	while (!ft_memchr(temp, '\n', ft_strlen(temp)) && rd > 0)
	{
		buf = ft_calloc(b_size + 1, sizeof(char));
		if (!buf)
			return (liberator(&temp, -1));
		rd = read(fd, buf, b_size);
		if (rd == -1)
			return (liberator(&buf, liberator(&temp, rd)));
		temp = joiner(temp, buf, rd);
		free(buf);
	}
	*line = get_line(temp);
	temp = trim_temp(temp);
	if (!ft_memchr(temp, '\n', ft_strlen(temp)) && rd == 0)
		return (liberator(&temp, rd));
	return (1);
}
