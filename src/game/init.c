/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 01:41:59 by maroy             #+#    #+#             */
/*   Updated: 2024/01/15 19:18:04 by maroy            ###   ########.fr       */
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


#define SIZE 64

char	*init_graphics(t_cub_file *cub, t_game *game)
{
	(void)cub;

	
	mlx_set_setting(MLX_MAXIMIZED, true);
	game->mlx = mlx_init( WIN_X, WIN_Y, WIN_TITLE, true);
	if (!game->mlx)
		return (GRAPHICS_INIT);
		

	int i;
	int j;
	
	j = 0;
	i = 0;
    mlx_image_t* img_un = mlx_new_image(game->mlx, SIZE, SIZE);

	mlx_image_t* img_zero = mlx_new_image(game->mlx, SIZE, SIZE);

	while (i < game->map_h)
	{
		j = 0;
		while (j < game->map_w)
		{
			if (game->map[i][j] == '1')
			{
				mlx_image_to_window(game->mlx, img_un, j * SIZE, i * SIZE);
				u_int32_t x = 0;
				u_int32_t y = 0;
				while(x < img_un->width - 1)
				{
					y = 0;
					while(y < img_un->height - 1)
					{
						mlx_put_pixel(img_un, x, y, 0x484e52FF);
						y++;
					}
					x++;
				}
			}
			else if (game->map[i][j] == '0')
			{
				mlx_image_to_window(game->mlx, img_zero, j * SIZE, i * SIZE);
				u_int32_t x = 0;
				u_int32_t y = 0;
				while(x < img_zero->width - 1)
				{
					y = 0;
					while(y < img_zero->height - 1 )
					{
						mlx_put_pixel(img_zero, x, y, 0xafb9c5FF);
						y++;
					}
					x++;
				}
			}
			// else if (game->map[i][j] == 'E' || game->map[i][j] == 'W'
			// 	|| game->map[i][j] == 'S' || game->map[i][j] == 'N')
			// {
			// 	mlx_image_to_window(game->mlx, img, j * 8, i * 8);
			// }
			// else
			// {
			// 	mlx_image_to_window(game->mlx, img, j * 8, i * 8);
			// }
			j++;
		}
		i++;
	}


	

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