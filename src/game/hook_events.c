/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:42:00 by maroy             #+#    #+#             */
/*   Updated: 2024/01/18 18:45:04 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		rect(mlx_image_t *img, t_shape shape, t_color color);
void	rect_fade(mlx_image_t *img, t_shape shape, t_color color);

static void	on_key_press(mlx_key_data_t keydata, t_game *game)
{
	keys_t	key;

	key = keydata.key;
	if (key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		destroy_game(game, true);
	else if (key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->p.rotate_l = true;
	else if (key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->p.rotate_r = true;
	else if (key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->p.move_no = true;
	else if (key == MLX_KEY_S && keydata.action == MLX_PRESS)
		game->p.move_so = true;
	else if (key == MLX_KEY_A && keydata.action == MLX_PRESS)
		game->p.move_we = true;
	else if (key == MLX_KEY_D && keydata.action == MLX_PRESS)
		game->p.move_ea = true;
}

static void	on_key_release(mlx_key_data_t keydata, t_game *game)
{
	keys_t	key;

	key = keydata.key;
	if (key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->p.rotate_l = false;
	else if (key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->p.rotate_r = false;
	else if (key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		game->p.move_no = false;
	else if (key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		game->p.move_so = false;
	else if (key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		game->p.move_we = false;
	else if (key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		game->p.move_ea = false;
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = param;
	on_key_press(keydata, game);
	on_key_release(keydata, game);
}

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

void	draw_floor_ceiling(t_game *game)
{
	t_shape	shape;
	
	shape.x = 0;
	shape.y = 0;
	shape.width = WIN_Y / 2;
	shape.height = WIN_X;
	rect_fade(game->img_screen, shape, game->color_c);
	shape.x = WIN_Y / 2;
	rect_fade(game->img_screen, shape, game->color_f);
}

void	my_loop(void *param)
{
	static t_ray	rays[RAYS_NB];
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
	ray_casting(game, rays);
	draw_floor_ceiling(game);
	draw_minimap(game, rays);
	mlx_image_to_window(game->mlx, game->img_screen, 0, 0);
}