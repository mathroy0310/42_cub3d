/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:42:00 by maroy             #+#    #+#             */
/*   Updated: 2024/01/16 21:34:29 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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