/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 01:41:59 by maroy             #+#    #+#             */
/*   Updated: 2023/11/21 16:12:23 by maroy            ###   ########.fr       */
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

bool	mid_row_valid(char **map, int row, char *dir)
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

char	*init_graphics(t_cub_file *cub, t_game *game)
{
	(void)cub;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (GRAPHICS_INIT);
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIN_X, WIN_Y, WIN_TITLE);
	if (!game->mlx_win)
		return (WINDOW_INIT);
	mlx_loop(game->mlx_ptr);
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