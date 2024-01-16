/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:25:53 by maroy             #+#    #+#             */
/*   Updated: 2024/01/15 21:04:08 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_image(mlx_image_t* img, uint32_t color)
{
	t_vect2u pos;

	pos = (t_vect2u){0, 0};
	while (pos.x < img->width - 1)
	{
		pos.y = 0;
		while (pos.y < img->height - 1)
		{
			mlx_put_pixel(img, pos.x, pos.y, color);
			pos.y++;
		}
		pos.x++;
	}
}