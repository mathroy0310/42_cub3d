/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:25:53 by maroy             #+#    #+#             */
/*   Updated: 2024/01/17 13:38:27 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		rect(mlx_image_t *img, t_shape shape, t_color color);
void		circle(mlx_image_t *img, t_shape s, t_color color);

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
	s.width = 4;
	s.height = s.width;
	s.x = (uint32_t)(game->p.pos.y * MINISIDE + sx - s.width / 2);
	s.y = (uint32_t)(game->p.pos.x * MINISIDE + sy - s.height / 2);
	rect(game->img_screen, s, MINI_COLOR_PLAYER);
}

void	draw_minimap(t_game *game)
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
	draw_walls_minimap(game, start_x, start_y, shape);
	draw_player_minimap(game, shape, start_x, start_y);
	draw_rays_minimap(game, shape, start_x, start_y);
}