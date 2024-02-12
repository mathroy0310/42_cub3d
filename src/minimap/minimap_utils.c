/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:35:21 by maroy             #+#    #+#             */
/*   Updated: 2024/02/12 14:52:53 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rect(mlx_image_t *img, t_shape shape, t_color color)
{
	uint32_t	i;
	uint32_t	j;

	i = shape.y;
	while (i < shape.y + shape.height && i < img->width)
	{
		j = shape.x;
		while (j < shape.x + shape.width && j < img->height)
		{
			mlx_put_pixel(img, i, j, color);
			++j;
		}
		++i;
	}
}

void	circle(mlx_image_t *img, t_shape s, t_color color)
{
	uint32_t	i;
	uint32_t	j;
	double		dist;

	i = s.y;
	while (i < s.y + s.height && i < img->width)
	{
		j = s.x;
		while (j < s.x + s.width && j < img->height)
		{
			dist = pow(i - (double)(s.y + s.height / 2.0), 2) + pow(j
					- (double)(s.x + s.width / 2.0), 2);
			if (dist < pow(s.width / 2.0, 2))
				mlx_put_pixel(img, i, j, color);
			++j;
		}
		++i;
	}
}

void	draw_line_angle(mlx_image_t *img, t_vect2d start, t_vect2d end,
		double angle)
{
	double	x;
	double	y;
	int		pixels;

	x = cos(angle);
	y = sin(angle);
	pixels = round(sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2))) + 2;
	while (pixels && start.x > 0 && start.y > 0 && start.x < img->width
		&& start.y < img->height)
	{
		mlx_put_pixel(img, start.x, start.y, MINI_COLOR_RAY);
		start.x += x;
		start.y += y;
		--pixels;
	}
}
