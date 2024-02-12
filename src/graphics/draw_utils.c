/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:25:49 by maroy             #+#    #+#             */
/*   Updated: 2024/02/12 15:09:31 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// documentation MLX42:
// In order to set each channel's byte we can use bit-shifting operations.

// A function that combines four individual channel bytes
// into a single integer using bit-shifting looks like this:
t_color	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	darken_color(uint32_t *color, double amount)
{
	t_vect3u	rgb;
	uint8_t		a;

	rgb.x = (uint8_t)ft_max(0, ((*color >> 24) & 0xFF) * amount);
	rgb.y = (uint8_t)ft_max(0, ((*color >> 16) & 0xFF) * amount);
	rgb.z = (uint8_t)ft_max(0, ((*color >> 8) & 0xFF) * amount);
	a = *color & 0xFF;
	*color = (rgb.x << 24) | (rgb.y << 16) | (rgb.z << 8) | a;
}
