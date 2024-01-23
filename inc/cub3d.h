/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:15:26 by maroy             #+#    #+#             */
/*   Updated: 2024/01/23 14:54:26 by rmarceau         ###   ########.fr       */
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

typedef unsigned int	t_color;

typedef struct s_shape
{
	uint32_t			x;
	uint32_t			y;
	uint32_t			width;
	uint32_t			height;
}						t_shape;

typedef enum e_direction
{
	NO,
	SO,
	WE,
	EA,
	NONE
}						t_direction;

typedef struct s_vect2u
{
	uint32_t			x;
	uint32_t			y;
}						t_vect2u;

typedef struct s_vect2d
{
	double				x;
	double				y;
}						t_vect2d;

typedef struct s_vect3d
{
	double				x;
	double				y;
	double				z;
}						t_vect3d;

typedef struct s_ray
{
	double				angle_rel;
	double				angle_abs;
	double				wall_dist;
	int32_t				wall_height;
	int32_t				draw_height;
	t_direction			wall_dir;
	t_vect2d			wall_hit;
}						t_ray;

typedef struct s_player
{
	t_vect2d			pos;
	double				dir;
	bool				move_no;
	bool				move_so;
	bool				move_we;
	bool				move_ea;
	bool				rotate_l;
	bool				rotate_r;

}						t_player;

typedef struct s_game
{
	t_player			p;
	t_color				color_f;
	t_color				color_c;
	bool				is_minimap;
	char				**map;
	int					map_w;
	int					map_h;
	mlx_t				*mlx;
	mlx_image_t			*img_screen;
	xpm_t				*xpm[NONE];
	mlx_image_t			*textures[NONE];
}						t_game;

int						get_rgba(int r, int g, int b, int a);
void					draw_minimap(t_game *game, t_ray *rays);

void					my_keyhook(mlx_key_data_t keydata, void *param);
void draw_walls(t_game * game, t_ray * rays);
void					my_loop(void *param);

void					update_player(t_game *game);

char					*init_game(t_cub_file *cub, t_game *game);
void					destroy_game(t_game *game, bool quit);
bool					is_mid_row_valid(char **map, int row, char *dir);
char					**make_char_map(t_list *raw_map);
int						max_list_str_len(t_list *lst);

void					debug_print_msg(char *msg);

/// @brief Utility function to print a message + number in debug mode
/// @param msg The message to print
/// @param format the arg message format
/// @param arg the first argument or NULL if format is 'f' or 'lf'
/// @param arg2 the second argument or NULL if format is 'd' or 'i' or 'u'
void					debug_print_number(char *msg, int format, int arg,
							double arg2);
void					debug_print_ray(t_ray *ray, int i);

void					ray_casting(t_game *game, t_ray *rays);
void					debug_print_map(t_game *game);
void					debug_print_colors(char *cat, t_vect3 color);

void					print_error(char *filename, char *error_msg);
void					print_error_then_exit(char *filename, char *error_msg);

#endif