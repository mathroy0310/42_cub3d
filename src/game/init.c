/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 01:41:59 by maroy             #+#    #+#             */
/*   Updated: 2024/02/12 15:26:37 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color		get_rgba(int r, int g, int b, int a);

static void	set_player_initial_pos(t_game *game)
{
	int		x;
	int		y;
	bool	done;

	y = -1;
	x = -1;
	done = false;
	while (!done && game->map[++y])
	{
		x = -1;
		while (!done && game->map[y][++x])
			if (ft_strchr("NSWE", game->map[y][x]))
				done = true;
	}
	game->p.pos.x = (double)x + 0.5;
	game->p.pos.y = (double)y + 0.5;
	if (game->map[y][x] == 'E')
		game->p.dir = 0.0;
	else if (game->map[y][x] == 'N')
		game->p.dir = 1.5 * M_PI;
	else if (game->map[y][x] == 'W')
		game->p.dir = M_PI;
	else
		game->p.dir = 0.5 * M_PI;
	game->map[y][x] = '0';
}

char	*init_graphics(t_cub_file *cub, t_game *game)
{
	game->mlx = mlx_init(WIN_X, WIN_Y, WIN_TITLE, false);
	if (!game->mlx)
		return (GRAPHICS_INIT);
	game->img_screen = mlx_new_image(game->mlx, WIN_X, WIN_Y);
	if (!game->img_screen)
		return (WINDOW_INIT);
	game->color_c = get_rgba(cub->color_c.r, cub->color_c.g, cub->color_c.b,
			255);
	game->color_f = get_rgba(cub->color_f.r, cub->color_f.g, cub->color_f.b,
			255);
	if (load_textures(cub, game))
		return (load_textures(cub, game));
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_image_to_window(game->mlx, game->img_screen, 0, 0);
	mlx_loop_hook(game->mlx, &my_loop, game);
	mlx_key_hook(game->mlx, &my_keyhook, game);
	mlx_loop(game->mlx);
	return (NULL);
}

char	*init_game(t_cub_file *cub, t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->map = make_char_map(cub->raw_map);
	if (!game->map)
		return (MALLOC_CHARMAP);
	game->map_w = max_list_str_len(cub->raw_map);
	game->map_h = ft_lstsize(cub->raw_map);
	game->is_minimap = false;
	if (((uint32_t)(game->map_w * MINISIDE) < WIN_X) && ((uint32_t)(game->map_h
				* MINISIDE) < WIN_Y))
		game->is_minimap = true;
	set_player_initial_pos(game);
	return (init_graphics(cub, game));
}

void	destroy_game(t_game *game, bool quit)
{
	if (game->map)
		ft_free_tab(game->map);
	mlx_terminate(game->mlx);
	if (quit)
		exit(EXIT_SUCCESS);
}
