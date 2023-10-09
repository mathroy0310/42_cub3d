/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 02:51:54 by maroy             #+#    #+#             */
/*   Updated: 2023/10/09 03:14:24 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	debug_print_msg(char *msg)
{
	if (DEBUG_MODE == true)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: -={ %s }=-", msg);
		printf(ANSI_COLOR_RESET"\n");
	}
}

void	debug_print_decimal(char *msg, int arg)
{
	if (DEBUG_MODE == true)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: %s --> -={ %d }=-", msg, arg);
		printf(ANSI_COLOR_RESET"\n");
	}
}

void	debug_print_colors(char *cat, t_vect3 color)
{
	if (DEBUG_MODE == true)
	{
		if (*cat == 'F' && color.r >= 0)
			printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: %s Color --> -={ r:%d, g:%d, b:%d }=-", "FLOOR", color.r, color.g, color.b);
		else if (*cat == 'C' && color.r >= 0)
			printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: %s Color --> -={ r:%d, g:%d, b:%d }=-", "CELLING", color.r, color.g, color.b);
		printf(ANSI_COLOR_RESET"\n");
	}
}


void	debug_print_map(t_game *game)
{
	if (DEBUG_MODE == true)
	{
		//DEBUG PRINT MAP WITH COLORS	
		int i = 0;
		int j = 0;
		debug_print_decimal("map_w", game->map_w);
		debug_print_decimal("map_h", game->map_h);
		while (i < game->map_h)
		{
			j = 0;
			while (j < game->map_w)
			{
				if (game->map[i][j] == '1')
					printf(ANSI_BG_COLOR_RED ANSI_COLOR_BRIGHT_RED"%c"ANSI_COLOR_RESET, game->map[i][j]);
				else if (game->map[i][j] == '0')
					printf(ANSI_BG_COLOR_GREEN ANSI_COLOR_BRIGHT_GREEN"%c"ANSI_COLOR_RESET, game->map[i][j]);
				else if (game->map[i][j] == 'E' || game->map[i][j] == 'W' || game->map[i][j] == 'S' || game->map[i][j] == 'N')
					printf(ANSI_BG_COLOR_BLUE ANSI_COLOR_BLACK"%c"ANSI_COLOR_RESET, game->map[i][j]);
				else
					printf(ANSI_BG_COLOR_YELLOW ANSI_COLOR_BRIGHT_YELLOW"%c"ANSI_COLOR_RESET, 'X');
				j++;
			}
			putchar((int)'\n');
			i++;
		}
	}
}

