/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:25:53 by maroy             #+#    #+#             */
/*   Updated: 2024/01/26 05:39:08 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		rect(mlx_image_t *img, t_shape shape, t_color color);
void		circle(mlx_image_t *img, t_shape s, t_color color);
void		draw_line_angle(mlx_image_t *img, t_vect2d start, t_vect2d end,
				double angle);

static void	draw_minimap_floor(t_game *game, int sx, int sy, t_shape shape)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	shape.width = MINISIDE;
	shape.height = MINISIDE;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			shape.x = y * MINISIDE + sx;
			shape.y = x * MINISIDE + sy;
			if (game->map[y][x] && game->map[y][x] == '0')
				rect(game->img_screen, shape, MINI_COLOR_FLOOR);
			x++;
		}
		y++;
	}
}

static void	draw_walls_minimap(t_game *game, int sx, int sy, t_shape shape)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			shape.x = y * MINISIDE + sx + 6;
			shape.y = x * MINISIDE + sy;
			if (game->map[y][x] && game->map[y][x] == '1')
				rect(game->img_screen, shape, MINI_COLOR_DARKWALL);
			shape.x = y * MINISIDE + sx;
			shape.y = x * MINISIDE + sy;
			if (game->map[y][x] && game->map[y][x] == '1')
				rect(game->img_screen, shape, MINI_COLOR_WALL);
			x++;
		}
		y++;
	}
}

static void	draw_player_minimap(t_game *game, t_shape s, int sx, int sy)
{
	s.width = 8;
	s.height = s.width;
	s.x = (uint32_t)(game->p.pos.y * MINISIDE + sx - s.width / 2);
	s.y = (uint32_t)(game->p.pos.x * MINISIDE + sy - s.height / 2);
	rect(game->img_screen, s, MINI_COLOR_PLAYER2);
	s.width = 6;
	s.height = s.width;
	s.x = (uint32_t)(game->p.pos.y * MINISIDE + sx - s.width / 2);
	s.y = (uint32_t)(game->p.pos.x * MINISIDE + sy - s.height / 2);
	rect(game->img_screen, s, MINI_COLOR_PLAYER);
}

void	draw_rays_minimap(t_game *game, t_ray *rays, int sx, int sy)
{
	t_vect2d	line_start;
	t_vect2d	line_end;
	int			i;

	line_start.x = game->p.pos.x * MINISIDE + sy;
	line_start.y = game->p.pos.y * MINISIDE + sx;
	i = -1;
	while (++i < RAYS_NB)
	{
		line_end.x = rays[i].wall_hit.x * MINISIDE + sy;
		line_end.y = rays[i].wall_hit.y * MINISIDE + sx;
		draw_line_angle(game->img_screen, line_start, line_end,
			rays[i].angle_abs);
	}
}

void	draw_minimap(t_game *game, t_ray *rays)
{
	t_shape shape;
	int start_y;
	int start_x;
	if (!game->is_minimap)
		return ;
	if (DEBUG_MODE)
		printf("DEBUG 🐞: drawing_minimap\n");
	shape.x = 0;
	shape.width = MINISIDE;
	shape.height = MINISIDE;
	start_y = game->img_screen->width - (game->map_w * MINISIDE + MINIPAD);
	start_x = game->img_screen->height - (game->map_h * MINISIDE + MINIPAD + 6);
	draw_minimap_floor(game, start_x, start_y, shape);
	draw_rays_minimap(game, rays, start_x, start_y);
	draw_walls_minimap(game, start_x, start_y, shape);
	draw_player_minimap(game, shape, start_x, start_y);
}