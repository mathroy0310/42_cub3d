/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 01:41:59 by maroy             #+#    #+#             */
/*   Updated: 2024/01/15 21:52:04 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	max_list_str_len(t_list *lst)
{
	t_list	*cur;
	int		max;
	int		len;

	cur = lst;
	max = 0;
	while (cur)
	{
		len = (int)ft_strlen(cur->content);
		if (len > max)
			max = len;
		cur = cur->next;
	}
	return (max);
}

bool	is_mid_row_valid(char **map, int row, char *dir)
{
	int	col;

	col = -1;
	while (map[row][++col])
	{
		if (col == 0 && ft_strchr("0NSWE", map[row][col]))
			return (false);
		if (ft_strchr("NSWE", map[row][col]))
		{
			if (*dir)
				return (false);
			*dir = map[row][col];
		}
		if (ft_strchr("0NSWE", map[row][col]) && (ft_strchr(" ", map[row][col
					+ 1]) || ft_strchr(" ", map[row][col - 1]) || ft_strchr(" ",
					map[row + 1][col]) || ft_strchr(" ", map[row - 1][col])
				|| ft_strchr(" ", map[row - 1][col + 1]) || ft_strchr(" ",
					map[row - 1][col - 1]) || ft_strchr(" ", map[row + 1][col
					+ 1]) || ft_strchr(" ", map[row + 1][col - 1])))
			return (false);
	}
	return (true);
}

char	**make_char_map(t_list *raw_map)
{
	size_t	width;
	size_t	height;
	size_t	i;
	t_list	*cur;
	char	**map;

	width = max_list_str_len(raw_map);
	height = ft_lstsize(raw_map);
	map = ft_calloc(height + 1, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	cur = raw_map;
	while (i < height)
	{
		map[i] = ft_calloc(width + 1, sizeof(char));
		if (!map[i])
		{
			ft_free_tab(map);
			return (NULL);
		}
		ft_memcpy(map[i++], cur->content, ft_strlen((char *)cur->content));
		cur = cur->next;
	}
	return (map);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game;

	game = param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		printf("ESCAPE\n");
	if ((keydata.key == MLX_KEY_W)
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		game->img_player->instances[0].y -= PLAYER_SPEED;
	if ((keydata.key == MLX_KEY_S)
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		game->img_player->instances[0].y += PLAYER_SPEED;
	if ((keydata.key == MLX_KEY_D)
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		game->img_player->instances[0].x += PLAYER_SPEED;
	if ((keydata.key == MLX_KEY_A) 
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		game->img_player->instances[0].x -= PLAYER_SPEED;
}

char	*init_graphics(t_cub_file *cub, t_game *game)
{
	(void)cub;

	int i = 0;
	int j = 0;
	t_vect2u player_pos;
	player_pos = (t_vect2u){0, 0};
	game->mlx = mlx_init( WIN_X, WIN_Y, WIN_TITLE, false);
	if (!game->mlx)
		return (GRAPHICS_INIT);

    mlx_image_t* img_un = mlx_new_image(game->mlx, GRID_SIZE, GRID_SIZE);
	mlx_image_t* img_zero = mlx_new_image(game->mlx, GRID_SIZE, GRID_SIZE);
	game->img_player = mlx_new_image(game->mlx, GRID_SIZE / 2, GRID_SIZE / 2);

	debug_print_decimal("Grid Size" , GRID_SIZE);

	while (i < game->map_h)
	{
		j = 0;
		while (j < game->map_w)
		{
			if (game->map[i][j] == '1')
			{
				mlx_image_to_window(game->mlx, img_un, j * GRID_SIZE, i * GRID_SIZE);
				fill_image(img_un, 0x484e52FF);
			}
			else if (game->map[i][j] == '0')
			{
				mlx_image_to_window(game->mlx, img_zero, j * GRID_SIZE, i * GRID_SIZE);
				fill_image(img_zero, 0xafb9c5FF);
			}
			else if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'W' || game->map[i][j] == 'E')
			{
				player_pos = (t_vect2u){j, i};
			}
			j++;
		}
		i++;
	}


	mlx_image_to_window(game->mlx, img_zero, player_pos.x * GRID_SIZE, player_pos.y * GRID_SIZE);
	mlx_image_to_window(game->mlx, game->img_player, player_pos.x * GRID_SIZE, player_pos.y * GRID_SIZE);
	fill_image(game->img_player, 0x53a352FF);
	mlx_key_hook(game->mlx, &my_keyhook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
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
	debug_print_map(game);
	return (init_graphics(cub, game));
}