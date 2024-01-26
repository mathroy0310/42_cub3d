/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:25:49 by maroy             #+#    #+#             */
/*   Updated: 2024/01/26 05:42:26 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// documentation MLX42:
// In order to set each channel's byte we can use bit-shifting operations.

// A function that combines four individual channel bytes into a single integer using bit-shifting looks like this:
t_color	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void darken_color(uint32_t *color, double amount)
{
    uint8_t r, g, b, a;

    r = (*color >> 24) & 0xFF;
    g = (*color >> 16) & 0xFF;
	b = (*color >> 8) & 0xFF;
    a = *color & 0xFF;

    r = (uint8_t)ft_max(0, r * amount);
    g = (uint8_t)ft_max(0, g * amount);
    b = (uint8_t)ft_max(0, b * amount);

    *color = (r << 24) | (g << 16) | (b << 8) | a;
}