/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:19:55 by maroy             #+#    #+#             */
/*   Updated: 2024/01/15 21:50:49 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

# include "MLX42.h"

/*	==== GLOBAL ==== */

# define WIN_TITLE "cub3D"

# define WIN_X 1280
# define WIN_Y 720

# define GRID_SIZE 16

/*	==== PLAYER ==== */

# define PLAYER_SPEED GRID_SIZE / 4


# define ERR_PROMPT "ERROR ❌: "

/*	==== PARSER ERRORS ==== */

# define PARSER_ARG_NB "Wrong number of arguments"
# define PARSER_ARG_EXT "Wrong file extension"
# define PARSER_ARG_OPEN "Cannot open file or is empty"
# define PARSER_XPM_EXT "All texture files must have XPM extension"
# define PARSER_XPM_OPN "Cannot open one of the texture files"
# define PARSER_LINE_FMT "A line is not correctly formatted"
# define PARSER_MAP_NOT_RDY "Not enough information before parsing map"
# define PARSER_MAP_CHAR "Map contains an invalid character"
# define PARSER_COLOR_LINE_ELEM "A color line has too many or too few elements"
# define PARSER_COLOR_LINE_CHAR "A color line contains non-numeric characters"
# define PARSER_COLOR_LINE_FMT "A color line is wrongly formatted"
# define PARSER_COLOR_ONCE "F and C should only be set once"
# define PARSER_COLOR_RANGE "Color must be R,G,B between 0 and 255"
# define PARSER_TEXTURE_LINE "Texture line error or direction already set"

/*	==== MALLOC ERRORS ==== */

# define MALLOC_SPLIT "Malloc error during split"
# define MALLOC_STRDUP "Malloc error while parsing cub map (strdup)"
# define MALLOC_LSTNEW "Malloc error while parsing cub map (lstnew)"
# define MALLOC_COLLINE "Malloc error while parsing color line"
# define MALLOC_CHARMAP "Malloc error while creating map in game init"
# define MALLOC_TEXTURE "Malloc error while initializing wall textures"

/*	==== CUBMAP MESSAGES ==== */
# define CUBMAP_NULL "Map is NULL"
# define CUBMAP_ROW_INV "A map row is not valid "
# define CUBMAP_DEF_DIR "No default direction found"

/*	==== GAME AND GRAPHICS MESSAGES ==== */
# define GRAPHICS_INIT "MinilibX initialization failed"
# define WINDOW_INIT "Cannot create new window"

/*  ==== COLOR CODES  ==== */

# define ANSI_COLOR_RESET "\x1b[0m"
# define ANSI_COLOR_BLACK "\x1b[30m"
# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN "\x1b[36m"
# define ANSI_COLOR_WHITE "\x1b[37m"
# define ANSI_COLOR_BRIGHT_BLACK "\x1b[30;1m"
# define ANSI_COLOR_BRIGHT_RED "\x1b[31;1m"
# define ANSI_COLOR_BRIGHT_GREEN "\x1b[32;1m"
# define ANSI_COLOR_BRIGHT_YELLOW "\x1b[33;1m"
# define ANSI_COLOR_BRIGHT_BLUE "\x1b[34;1m"
# define ANSI_COLOR_BRIGHT_MAGENTA "\x1b[35;1m"
# define ANSI_COLOR_BRIGHT_CYAN "\x1b[36;1m"
# define ANSI_COLOR_BRIGHT_WHITE "\x1b[37;1m"
# define ANSI_BG_COLOR_BLACK "\x1b[40m"
# define ANSI_BG_COLOR_RED "\x1b[41m"
# define ANSI_BG_COLOR_GREEN "\x1b[42m"
# define ANSI_BG_COLOR_YELLOW "\x1b[43m"
# define ANSI_BG_COLOR_BLUE "\x1b[44m"
# define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
# define ANSI_BG_COLOR_CYAN "\x1b[46m"
# define ANSI_BG_COLOR_WHITE "\x1b[47m"
# define ANSI_BG_COLOR_BRIGHT_BLACK "\x1b[40;1m"
# define ANSI_BG_COLOR_BRIGHT_RED "\x1b[41;1m"
# define ANSI_BG_COLOR_BRIGHT_GREEN "\x1b[42;1m"
# define ANSI_BG_COLOR_BRIGHT_YELLOW "\x1b[43;1m"
# define ANSI_BG_COLOR_BRIGHT_BLUE "\x1b[44;1m"
# define ANSI_BG_COLOR_BRIGHT_MAGENTA "\x1b[45;1m"
# define ANSI_BG_COLOR_BRIGHT_CYAN "\x1b[46;1m"
# define ANSI_BG_COLOR_BRIGHT_WHITE "\x1b[47;1m"
# define ANSI_STYLE_BOLD "\x1b[1m"
# define ANSI_STYLE_UNDERLINE "\x1b[4m"
# define ANSI_STYLE_REVERSED "\x1b[7m"

#endif