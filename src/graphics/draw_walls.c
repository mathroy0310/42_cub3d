/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:56:26 by maroy             #+#    #+#             */
/*   Updated: 2024/02/12 14:58:25 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_color	get_pixel_color(mlx_texture_t *tex, int tx, int ty)
{
	uint8_t	*dst;

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
