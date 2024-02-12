/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:06:40 by maroy             #+#    #+#             */
/*   Updated: 2024/02/12 14:59:08 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cub3d.h"

char	*load_textures(t_cub_file *cub, t_game *game);
void	draw_screen(t_game *game, t_ray *rays);

t_color	get_rgba(int r, int g, int b, int a);

/*-- draw_walls --*/
void	draw_no_so_walls(t_game *game, t_ray *ray, int sx, int sy);
void	draw_ea_we_walls(t_game *game, t_ray *ray, int sx, int sy);
#endif
