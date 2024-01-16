/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:15:26 by maroy             #+#    #+#             */
/*   Updated: 2024/01/15 21:54:11 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "defines.h"
# include "libft.h"
# include "parsing.h"
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_direction
{
	NO,
	SO,
	WE,
	EA,
	NONE
}			t_direction;

typedef struct s_vect2u
{
	uint32_t		x;
	uint32_t		y;
}			t_vect2u;

typedef struct s_player
{
	t_vect2u	pos;
	
}			t_player;

typedef struct s_game
{
	char	**map;
	int		map_w;
	int		map_h;
	mlx_t 	*mlx;
	mlx_image_t *img_player; // a enlever
}			t_game;

void		fill_image(mlx_image_t* img, uint32_t color);


char		*init_game(t_cub_file *cub, t_game *game);
bool		is_mid_row_valid(char **map, int row, char *dir);
char		**make_char_map(t_list *raw_map);
int			max_list_str_len(t_list *lst);

void		debug_print_msg(char *msg);
void		debug_print_decimal(char *msg, int arg);
void		debug_print_map(t_game *game);
void		debug_print_colors(char *cat, t_vect3 color);

void		print_error(char *filename, char *error_msg);
void		print_error_then_exit(char *filename, char *error_msg);

#endif