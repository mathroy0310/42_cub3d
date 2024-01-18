/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 01:41:59 by maroy             #+#    #+#             */
/*   Updated: 2024/01/18 16:23:53 by rmarceau         ###   ########.fr       */
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

static inline void	set_player_initial_pos(t_game *game)
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
	game->color_c = get_rgba(cub->color_c.r, cub->color_c.g, cub->color_c.b, 255);
	game->color_f = get_rgba(cub->color_f.r, cub->color_f.g, cub->color_f.b, 255);
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
	if (((u_int32_t)(game->map_w * MINISIDE) < WIN_X)
		&& ((u_int32_t)(game->map_h * MINISIDE) < WIN_Y))
		game->is_minimap = true;
	debug_print_map(game);
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