/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:51:54 by maroy             #+#    #+#             */
/*   Updated: 2024/01/17 19:15:21 by maroy            ###   ########.fr       */
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

void	debug_print_colors(char *cat, t_vect3 color)
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

void	debug_print_map(t_game *game)
{
	int	i;
	int	j;

	if (DEBUG_MODE == true)
	{
		// DEBUG PRINT MAP WITH COLORS
		i = 0;
		j = 0;
		debug_print_number("map_w", 'd', game->map_w, 0);
		debug_print_number("map_h", 'd',game->map_h, 0);
		while (i < game->map_h)
		{
			j = 0;
			while (j < game->map_w)
			{
				if (game->map[i][j] == '1')
					printf(ANSI_BG_COLOR_RED ANSI_COLOR_BRIGHT_RED "%c" ANSI_COLOR_RESET,
						game->map[i][j]);
				else if (game->map[i][j] == '0')
					printf(ANSI_BG_COLOR_GREEN ANSI_COLOR_BRIGHT_GREEN "%c" ANSI_COLOR_RESET,
						game->map[i][j]);
				else if (game->map[i][j] == 'E' || game->map[i][j] == 'W'
					|| game->map[i][j] == 'S' || game->map[i][j] == 'N')
					printf(ANSI_BG_COLOR_BLUE ANSI_COLOR_BLACK "%c" ANSI_COLOR_RESET,
						game->map[i][j]);
				else
					printf(ANSI_BG_COLOR_YELLOW ANSI_COLOR_BRIGHT_YELLOW "%c" ANSI_COLOR_RESET,
						'X');
				j++;
			}
			putchar((int)'\n');
			i++;
		}
	}
}
