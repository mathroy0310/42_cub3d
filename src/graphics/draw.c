/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:01:36 by maroy             #+#    #+#             */
/*   Updated: 2024/01/24 18:21:55 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					get_texture_x(t_ray ray);

static void darken_color(uint32_t *color, double amount)
{
    uint8_t r, g, b, a;

    r = (*color >> 24) & 0xFF;
    g = (*color >> 16) & 0xFF;
	b = (*color >> 8) & 0xFF;
    a = *color & 0xFF;

    r = (uint8_t)ft_max(0, r * amount);
    g = (uint8_t)ft_max(0, g * amount);
    b = (uint8_t)ft_max(0, b * amount);

    *color = (r << 24) | (g << 16) | (b << 8) | a;
}

static void draw_walls(t_game *game , t_ray *ray, int startx, int starty)
{
	(void)game;
	(void)startx;
	(void)starty;
	if (ray->wall_dir == NO || ray->wall_dir == SO)
		//draw_no_so_wall();
		return;
	else if (ray->wall_dir == WE || ray->wall_dir == EA)
		//draw_we_ea_wall();
		return;
}

void	draw_screen(t_game *game, t_ray *rays)
{
	uint32_t	i;
	uint32_t	x;
	uint32_t	y;
	t_color	color;

	i = -1;
	while (++i < RAYS_NB)
	{
		rays[i].wall_dist *= cos(game->p.dir - rays[i].angle_abs);
		rays[i].wall_height = (int32_t)(WIN_Y / rays[i].wall_dist);
		rays[i].draw_height = rays[i].wall_height;
		if (rays[i].draw_height > WIN_Y)
			rays[i].draw_height = WIN_Y;
		y = -1;
		while (++y < (uint32_t)(WIN_Y - rays[i].draw_height) / 2)
		{
			x = i * round(WIN_X / RAYS_NB) - 1;
			while (++x < (i + 1) * (round(WIN_X / RAYS_NB)))
			{
				color = game->color_c;
				darken_color(&color, 0.2 + 0.75 *  (1 - (double)y / WIN_Y));
				mlx_put_pixel(game->img_screen, x, y, color);
		
				color = game->color_f;
				darken_color(&color, 0.75 + 0.5 * (1 - (double)(WIN_Y - 1 - y) / WIN_Y));
				mlx_put_pixel(game->img_screen, x, WIN_Y -  1 - y, color);
			}
			draw_walls(game, &rays[i], i * round(WIN_X / RAYS_NB), 0);
		}
	}
}