/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:01:36 by maroy             #+#    #+#             */
/*   Updated: 2024/01/26 05:43:45 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_texture_x(t_ray ray);
t_color	get_rgba(int r, int g, int b, int a);
void	darken_color(uint32_t *color, double amount);

t_color	get_pixel_color(mlx_texture_t *tex, int tx, int ty)
{
	uint8_t		*dst;
	
	dst = tex->pixels + 4 * (ty * tex->width + tx);
	return (get_rgba(dst[0], dst[1], dst[2], dst[3]));
}

void	draw_no_so_walls(t_game *game, t_ray *ray, int sx, int sy)
{
	int				x;
	int				y;
	int				tx;
	int				ty;
	mlx_texture_t	*tex;

	if (ray->wall_dir == NO)
		tex = game->textures[NO];
	else
		tex = game->textures[SO];
	y = -1;
	while (++y < ray->draw_height)
	{
		tx = (int)((ray->wall_hit.x - floor(ray->wall_hit.x))
				* (double)(tex->width));
		ty = (int)(((double)y / ray->wall_height + (1.0
						- (double)ray->draw_height / ray->wall_height) / 2.0)
				* tex->height);
		x = -1;
		while (++x < (WIN_X / RAYS_NB))
			mlx_put_pixel(game->img_screen, sx + x, sy + y, get_pixel_color(tex,
					tx, ty));
	}
}

void	draw_ea_we_walls(t_game *game, t_ray *ray, int sx, int sy)
{
	int				x;
	int				y;
	int				tx;
	int				ty;
	mlx_texture_t	*tex;

	if (ray->wall_dir == WE)
		tex = game->textures[WE];
	else
		tex = game->textures[EA];
	y = -1;
	while (++y < ray->draw_height)
	{
		tx = (int)((ray->wall_hit.y - floor(ray->wall_hit.y))
				* (double)(tex->width));
		ty = (int)(((double)y / ray->wall_height + (1.0
						- (double)ray->draw_height / ray->wall_height) / 2.0)
				* tex->height);
		x = -1;
		while (++x < (WIN_X / RAYS_NB))
			mlx_put_pixel(game->img_screen, sx + x, sy + y, get_pixel_color(tex,
					tx, ty));
	}
}

void	draw_walls(t_game *game, t_ray *ray, int startx, int starty)
{
	if (ray->wall_dir == NO || ray->wall_dir == SO)
		draw_no_so_walls(game, ray, startx, starty);
	else if (ray->wall_dir == WE || ray->wall_dir == EA)
		draw_ea_we_walls(game, ray, startx, starty);
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
		int wall_start_y = round((WIN_Y - rays[i].draw_height) / 2.0);
		while (++y < wall_start_y)
		{
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
		draw_walls(game, &rays[i], i * (WIN_X / RAYS_NB), y);
	}
}