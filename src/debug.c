/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:51:54 by maroy             #+#    #+#             */
/*   Updated: 2024/01/26 05:50:16 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug_print_msg(char *msg)
{
	if (DEBUG_MODE == true)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: -={ %s }=-", msg);
		printf(ANSI_COLOR_RESET "\n");
	}
}

void	debug_print_ray(t_ray *ray, int i)
{
	if (DEBUG_MODE)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: -={ ray : {%d} }=-\n", i);
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: -={ ray->angle_rel : {%lf} }=-\n", ray->angle_rel);
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: -={ ray->angle_abs : {%lf} }=-\n", ray->angle_abs);
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: -={ ray->wall_dist : {%lf} }=-\n", ray->wall_dist);
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: -={ ray->wall_hit.y : {%f} }=-\n", ray->wall_hit.y);
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: -={ ray->wall_hit.x : {%f} }=-\n", ray->wall_hit.x);
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: -={ ray->dir : {%d} }=-\n", ray->wall_dir);
		
	}

}

void	debug_print_number(char *msg, int format, int arg, double arg2)
{
	if (DEBUG_MODE == true)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE);
		if (format == 'd' || format == 'i')
			printf("DEBUG 🐞: %s --> -={ %d }=-", msg, arg);
		if (format == 'u')
			printf("DEBUG 🐞: %s --> -={ %u }=-", msg, arg);
		if (format == 'f')
			printf("DEBUG 🐞: %s --> -={ %lf }=-", msg, arg2);
		printf(ANSI_COLOR_RESET "\n");
	}
}

void	debug_print_colors(char *cat, t_vect3i color)
{
	if (DEBUG_MODE == true)
	{
		if (*cat == 'F' && color.r >= 0)
			printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: %s Color --> -={ r:%d, g:%d, b:%d}=-", 
					"FLOOR",
					color.r,
					color.g,
					color.b);
		else if (*cat == 'C' && color.r >= 0)
			printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: %s Color --> -={ r:%d, g:%d, b:%d}=-",
					"CELLING",
					color.r,
					color.g,
					color.b);
	printf(ANSI_COLOR_RESET "\n");
	}
}
