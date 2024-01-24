/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:38:45 by maroy             #+#    #+#             */
/*   Updated: 2024/01/24 18:44:53 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include <stdint.h>
# include <stdbool.h>
# include "ft_vect.h"
# include "ft_list.h"
# include "MLX42.h"

typedef unsigned int	t_color;

 // PARSING

typedef struct s_vect3i
{
	int		r;
	int		g;
	int		b;
}			t_vect3i;

typedef enum e_direction
{
	NO,
	SO,
	WE,
	EA,
	NONE
}						t_direction;

typedef struct s_cub_file
{
	char	*tex_path[NONE];
	t_vect3i	color_c;
	t_vect3i	color_f;
	t_list	*raw_map;
}			t_cub_file;




typedef struct s_shape
{
	uint32_t			x;
	uint32_t			y;
	uint32_t			width;
	uint32_t			height;
}						t_shape;

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
	mlx_texture_t		*textures[NONE];
}						t_game;

#endif // 