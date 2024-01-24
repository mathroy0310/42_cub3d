/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:15:26 by maroy             #+#    #+#             */
/*   Updated: 2024/01/24 14:43:06 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include "libft.h"


# include "typedefs.h"
# include "defines.h"
# include "graphics.h"
# include "parsing.h"


int						get_rgba(int r, int g, int b, int a);
void					draw_minimap(t_game *game, t_ray *rays);

void					my_keyhook(mlx_key_data_t keydata, void *param);
void					my_loop(void *param);

void					update_player(t_game *game);

char					*init_game(t_cub_file *cub, t_game *game);
void					destroy_game(t_game *game, bool quit);
bool					is_mid_row_valid(char **map, int row, char *dir);
char					**make_char_map(t_list *raw_map);
int						max_list_str_len(t_list *lst);

void					debug_print_msg(char *msg);
void					debug_print_number(char *msg, int format, int arg,
							double arg2);
void					debug_print_ray(t_ray *ray, int i);
void					debug_print_map(t_game *game);
void					debug_print_colors(char *cat, t_vect3i color);


void					print_error(char *filename, char *error_msg);
void					print_error_then_exit(char *filename, char *error_msg);

#endif