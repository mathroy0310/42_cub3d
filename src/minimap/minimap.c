/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:25:53 by maroy             #+#    #+#             */
/*   Updated: 2024/01/17 16:43:11 by maroy            ###   ########.fr       */
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

void	draw_line(t_game *game, t_vect2u p1, t_vect2u p2)
{
	int dx = ft_abs(p2.x - p1.x);
	int dy = -ft_abs(p2.y - p1.y);
	int sx = p1.x < p2.x ? 1 : -1;
	int sy = p1.y < p2.y ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1)
	{
		mlx_put_pixel(game->img_screen, p1.y, p1.x, MINI_COLOR_RAY);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			if (p1.x == p2.x)
				break ;
			err += dy;
			p1.x += sx;
		}
		if (e2 <= dx)
		{
			if (p1.y == p2.y)
				break ;
			err += dx;
			p1.y += sy;
		}
	}
	
}

void	draw_rays_minimap(t_game *game, int sx, int sy)
{
	t_vect2u p1;
	t_vect2u p2;

	p1.x = (uint32_t)(game->p.pos.y * MINISIDE + sx);
	p1.y = (uint32_t)(game->p.pos.x * MINISIDE + sy);

	double angle = game->p.dir;

	p2.y = p1.y + (int)(cos(angle) * 100);
	p2.x = p1.x + (int)(sin(angle) * 100);

	if (DEBUG_MODE)
	{
		printf("DEBUG 🐞: p1.x --> -={ %d }=-\n", p1.x);
		printf("DEBUG 🐞: p1.y --> -={ %d }=-\n", p1.y);

		printf("DEBUG 🐞: p2.x --> -={ %d }=-\n", p2.x);
		printf("DEBUG 🐞: p2.y --> -={ %d }=-\n", p2.y);

		printf("DEBUG 🐞: angle --> -={ %lf }=-\n\n", angle);
	}

	draw_line(game, p1, p2);
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
	draw_rays_minimap(game, start_x, start_y);
}