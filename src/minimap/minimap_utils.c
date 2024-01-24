/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:35:21 by maroy             #+#    #+#             */
/*   Updated: 2024/01/24 13:40:54 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// documentation MLX42:
// In order to set each channel's byte we can use bit-shifting operations.

// A function that combines four individual channel bytes into a single integer using bit-shifting looks like this:
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

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
			//printf("[DEBUG] minimap pixel coord : i: %d, j: %d\n", i, j);
			mlx_put_pixel(img, i, j, color);
			++j;
		}
		++i;
	}
}

void	circle(mlx_image_t *img, t_shape s, t_color color)
{
	uint32_t i;
	uint32_t j;
	double dist;

	i = s.y;
	while (i < s.y + s.height && i < img->width)
	{
		j = s.x;
		while (j < s.x + s.width && j < img->height)
		{
			dist = sqrt(pow(i - (s.y + s.height / 2), 2) + pow(j - (s.x
							+ s.width / 2), 2));
			if (dist < s.width / 2.0)
				mlx_put_pixel(img, i, j, color);
			++j;
		}
		++i;
	}
}

void	draw_line_angle(mlx_image_t *img, t_vect2d start, t_vect2d end, double angle)
{
	double x;
	double y;
	int pixels;

	x = cos(angle);
	y = sin(angle);
	pixels = round(sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2))) + 2;
	while (pixels && start.x > 0 && start.y > 0 && start.x < img->width && start.y < img->height)
	{
		mlx_put_pixel(img, start.x, start.y, MINI_COLOR_RAY);
		start.x += x;
		start.y += y;
		--pixels;
	}
	
}