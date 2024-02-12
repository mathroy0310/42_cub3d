/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 05:47:05 by maroy             #+#    #+#             */
/*   Updated: 2024/02/12 13:23:04 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	distance_points(t_vect2d *p1, t_vect2d *p2)
{
	return (sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2)));
}

double	get_intersect(t_vect3d *line, double value, bool is_h)
{
	if ((is_h && line->x == 0.0) || (!is_h && line->y == 0.0))
		return (INFINITY);
	if (is_h)
		return ((line->z + line->y * value) / (-line->x));
	return ((line->z + line->x * value) / (-line->y));
}

void	get_line_equation(t_vect2d *pt, double angle, t_vect3d *line)
{
	if (cos(angle) == 0.0)
	{
		line->x = 1.0;
		line->y = 0.0;
		line->z = -pt->x;
		return ;
	}
	line->x = tan(angle);
	line->y = -1.0;
	line->z = pt->y - line->x * pt->x;
}
