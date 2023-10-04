/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:19:55 by maroy             #+#    #+#             */
/*   Updated: 2023/10/03 18:10:58 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*	==== GLOBAL ==== */

# define WINDOW_TITLE "cub3D"
# define WIN_X		900
# define WIN_Y		700

/*	==== LINUX ==== */
# ifdef __linux__
#  define USING_LINUX 1
#  include "../libs/minilibx-linux/mlx.h"
#  include <X11/X.h>
#  define KEY_ESC 65307
#  define KEY_LEFT_ARROW 65361
#  define KEY_UP_ARROW 65362
#  define KEY_RIGHT_ARROW 65363
#  define KEY_DOWN_ARROW 65364
/*	==== MACOS ==== */
# else
#  define USING_LINUX 0
#  include "../libs/minilibx-mac/mlx.h"
#  define KEY_ESC 53
#  define KEY_LEFT_ARROW 123
#  define KEY_UP_ARROW 126
#  define KEY_RIGHT_ARROW 124
#  define KEY_DOWN_ARROW 125

# endif

# define ERR_PROMPT "ERROR ❌: "

/*	==== PARSER ERRORS ==== */

# define PARSER_XPM_EXT			"All texture files must have XPM extension"
# define PARSER_XPM_OPN			"Cannot open one of the texture files"
# define PARSER_LINE_FMT		"A line is not correctly formatted"
# define PARSER_MAP_NOT_RDY		"Not enough information before parsing map"
# define PARSER_MAP_CHAR		"Map contains an invalid character"
# define PARSER_COLOR_LINE_ELEM	"A color line has too many or too few elements"
# define PARSER_COLOR_LINE_CHAR	"A color line contains non-numeric characters"
# define PARSER_COLOR_LINE_FMT	"A color line is wrongly formatted"
# define PARSER_COLOR_ONCE		"F and C should only be set once"
# define PARSER_COLOR_RANGE		"Color must be R,G,B between 0 and 255"
# define PARSER_TEXTURE_LINE	"Texture line error or direction already set"

/*	==== MALLOC ERRORS ==== */

# define MALLOC_SPLIT	"Malloc error during split"
# define MALLOC_STRDUP	"Malloc error while parsing cub map (strdup)"
# define MALLOC_LSTNEW	"Malloc error while parsing cub map (lstnew)"
# define MALLOC_COLLINE	"Malloc error while parsing color line"
# define MALLOC_CHARMAP	"Malloc error while creating map in game init"
# define MALLOC_TEXTURE	"Malloc error while initializing wall textures"

/*  ==== Color Codes for users  ==== */

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