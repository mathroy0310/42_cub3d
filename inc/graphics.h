/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:06:40 by maroy             #+#    #+#             */
/*   Updated: 2024/01/24 14:42:51 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cub3d.h"

char *load_textures(t_cub_file *cub, t_game *game);
void	draw_screen(t_game *game, t_ray *rays);

#endif