/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:01:36 by maroy             #+#    #+#             */
/*   Updated: 2024/02/12 14:58:47 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	darken_color(uint32_t *color, double amount);

void	draw_walls(t_game *game, t_ray *ray, int startx, int starty)
{
	if (ray->wall_dir == NO || ray->wall_dir == SO)
		draw_no_so_walls(game, ray, startx, starty);
	else if (ray->wall_dir == WE || ray->wall_dir == EA)
		draw_ea_we_walls(game, ray, startx, starty);
}

void	draw_floor_ceiling(int i, int y, t_game *game)
{
	int		x;
	t_color	color;

	x = i * (WIN_X / RAYS_NB) - 1;
	while (++x < (i + 1) * (WIN_X / RAYS_NB))
	{
		color = game->color_c;
		darken_color(&color, 0.2 + 0.75 * (1 - (double)y / WIN_Y));
		mlx_put_pixel(game->img_screen, x, y, color);
		color = game->color_f;
		darken_color(&color, 0.75 + 0.5 * (1 - (double)(WIN_Y - 1 - y)
				/ WIN_Y));
		mlx_put_pixel(game->img_screen, x, WIN_Y - 1 - y, color);
	}
}

void	draw_screen(t_game *game, t_ray *rays)
{
	int	i;
	int	y;

	i = -1;
	while (++i < RAYS_NB)
	{
		rays[i].wall_dist *= cos(game->p.dir - rays[i].angle_abs);
		rays[i].wall_height = (int32_t)(WIN_Y / rays[i].wall_dist);
		rays[i].draw_height = rays[i].wall_height;
		if (rays[i].draw_height > WIN_Y)
			rays[i].draw_height = WIN_Y;
		y = -1;
		while (++y < round((WIN_Y - rays[i].draw_height) / 2.0))
			draw_floor_ceiling(i, y, game);
		draw_walls(game, &rays[i], i * (WIN_X / RAYS_NB), y);
	}
}
