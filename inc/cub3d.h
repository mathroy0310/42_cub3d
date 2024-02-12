/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:15:26 by maroy             #+#    #+#             */
/*   Updated: 2024/02/12 15:27:57 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
//
# include "typedefs.h"
# include "defines.h"
# include "parsing.h"
# include "graphics.h"
//
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

t_color	get_rgba(int r, int g, int b, int a);
void	draw_minimap(t_game *game, t_ray *rays);

void	my_keyhook(mlx_key_data_t keydata, void *param);
void	my_loop(void *param);

void	update_player(t_game *game);

char	*init_game(t_cub_file *cub, t_game *game);
void	destroy_game(t_game *game, bool quit);
bool	is_mid_row_valid(char **map, int row, char *dir);
char	**make_char_map(t_list *raw_map);
int		max_list_str_len(t_list *lst);

void	print_error(char *filename, char *error_msg);
void	print_error_then_exit(char *filename, char *error_msg);

#endif
