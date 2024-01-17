/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:11:27 by maroy             #+#    #+#             */
/*   Updated: 2024/01/17 15:06:03 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline bool	is_player_moving(t_player *p)
{
	static bool	first_run = true;

	if (first_run)
	{
		first_run = false;
		return (true);
	}
	return (p->move_no || p->move_so || p->move_we || p->move_ea || p->rotate_l
		|| p->rotate_r);
}

static inline bool	is_moving_diagonal(t_game *game)
{
	return ((game->p.move_no && game->p.move_ea) || (game->p.move_no
			&& game->p.move_we) || (game->p.move_so && game->p.move_ea)
		|| (game->p.move_so && game->p.move_we));
}

static void	player_rotate(t_game *game, double angle)
{
	double	dir;

	dir = angle + game->p.dir;
	if (dir < 0.0)
		game->p.dir = dir + M_PI_PI;
	else if (dir >= M_PI_PI)
		game->p.dir = dir - M_PI_PI;
	else
		game->p.dir = dir;
}

static bool can_player_move(t_game *game, double dx, double dy)
{
	double const	lim_wall = 0.05;
	double			x;
	double			y;

	x = game->p.pos.x + dx;
	y = game->p.pos.y + dy;
	return (0 <= x && x < WIN_X && 0 <= y && y < WIN_Y
		&& game->map[(int)(y + lim_wall)][(int)(x + lim_wall)] == '0'
		&& game->map[(int)(y - lim_wall)][(int)(x - lim_wall)] == '0'
		&& game->map[(int)(y + lim_wall)][(int)(x - lim_wall)] == '0'
		&& game->map[(int)(y - lim_wall)][(int)(x + lim_wall)] == '0');
}

static void	player_move(t_game *game, double speed, double angle)
{
	double const	diag_speed = PLAYER_MOV_SPEED / sqrt(2.5);
	double			dx;
	double			dy;

	angle += game->p.dir;
	if (is_moving_diagonal(game))
		speed = diag_speed;
	dx = speed * cos(angle);
	dy = speed * sin(angle);
	game->p.pos.x += dx;
	game->p.pos.y += dy;
	if (!can_player_move(game, dx, dy))
	{
		game->p.pos.x -= dx;
		game->p.pos.y -= dy;
	}
}

static void	update_player(t_game *game)
{
	if (game->p.rotate_l)
		player_rotate(game, -PLAYER_ROT_SPEED);
	if (game->p.rotate_r)
		player_rotate(game, PLAYER_ROT_SPEED);
	if (game->p.move_no)
		player_move(game, PLAYER_MOV_SPEED, 0.0);
	if (game->p.move_so)
		player_move(game, PLAYER_MOV_SPEED, M_PI);
	if (game->p.move_we)
		player_move(game, PLAYER_MOV_SPEED, -M_PI_2);
	if (game->p.move_ea)
		player_move(game, PLAYER_MOV_SPEED, M_PI_2);
}

void	my_loop(void *param)
{
	t_game	*game;

	game = param;
	if (!is_player_moving(&game->p))
		return ;
	update_player(game);
	if (DEBUG_MODE)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE"DEBUG 🐞: game->p.pos.y --> -={ %lf }=-\n", game->p.pos.y);
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: game->p.pos.x --> -={ %lf }=-\n", game->p.pos.x);
		printf(ANSI_COLOR_BRIGHT_BLUE"DEBUG 🐞: game->p.dir --> -={ %lf }=-\n", game->p.dir);
	}
	mlx_delete_image(game->mlx, game->img_screen);
	game->img_screen = mlx_new_image(game->mlx, WIN_X, WIN_Y);
	mlx_image_to_window(game->mlx, game->img_screen, 0, 0);
	draw_minimap(game);
}
