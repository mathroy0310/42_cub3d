/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:01:36 by maroy             #+#    #+#             */
/*   Updated: 2024/01/24 19:50:22 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			get_texture_x(t_ray ray);
int			get_rgba(int r, int g, int b, int a);
void		darken_color(uint32_t *color, double amount);

static void	draw_walls(t_game *game, t_ray *ray, int startx, int starty)
{
	int	y;
	int x;

	(void)game;
	(void)startx;
	(void)starty;
	if (ray->wall_dir == NO)
	{
		// draw_no_so_wall();
		y = -1;
		while (++y < ray->draw_height)
		{
			x = -1;
			int texture_x = (ray->wall_hit.x - floor(ray->wall_hit.x) * (game->textures[NO]->width));
			int texture_y = (y - (WIN_Y - ray->draw_height) / 2) * ((float)IMG_SIZE / ray->draw_height);
			printf(" textrue x %d\n", texture_x);
			printf(" textrue y %d\n", texture_y);
			// while (++x < (WIN_X / RAYS_NB))
			// 	mlx_put_pixel(game->img_screen, starty + y, startx + x, get_color(game->textures[NO], texture_x, texture_y));
		}
		return ;
	}
	else if (ray->wall_dir == WE || ray->wall_dir == EA || ray->wall_dir == SO)
		// draw_we_ea_wall();
		return ;
}

void	draw_screen(t_game *game, t_ray *rays)
{
	int i;
	int x;
	int y;
	t_color color;

	i = -1;
	while (++i < RAYS_NB)
	{
		rays[i].wall_dist *= cos(game->p.dir - rays[i].angle_abs);
		rays[i].wall_height = (int32_t)(WIN_Y / rays[i].wall_dist);
		rays[i].draw_height = rays[i].wall_height;
		if (rays[i].draw_height > WIN_Y)
			rays[i].draw_height = WIN_Y;
		y = -1;
		while (++y < (WIN_Y - rays[i].draw_height) / 2)
		{
			x = i * ((WIN_X / RAYS_NB)) - 1;
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
		draw_walls(game, &rays[i], i * (WIN_X / RAYS_NB), y);
	}
}