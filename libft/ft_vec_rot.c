/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:38:48 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/19 16:53:54 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vec_rot(float *vec_x, float *vec_y, float angle)
{
	float	old_vec_x;
	float	old_vec_y;

	old_vec_x = *vec_x;
	old_vec_y = *vec_y;
	*vec_x = old_vec_x * cos(angle) - old_vec_y * sin(angle);
	*vec_y = old_vec_x * sin(angle) + old_vec_y * cos(angle);
}
