/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:12:41 by maroy             #+#    #+#             */
/*   Updated: 2024/01/24 18:46:22 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	ready_to_parse_map(t_cub_file *cub)
{
	bool	textures_ready;
	bool	colors_ready;

	textures_ready = (cub->tex_path[NO] && cub->tex_path[SO] && cub->tex_path[WE]
			&& cub->tex_path[EA]);
	colors_ready = (cub->color_f.r >= 0 && cub->color_f.g >= 0
			&& cub->color_f.b >= 0 && cub->color_c.r >= 0 && cub->color_c.g >= 0
			&& cub->color_c.b >= 0);
	return (textures_ready && colors_ready);
}

char	*parse_cub_line_map(t_cub_file *cub, char *line)
{
	int		i;
	char	*content;
	t_list	*elem;

	if (!ready_to_parse_map(cub))
		return (PARSER_MAP_NOT_RDY);
	i = -1;
	while (line[++i])
		if (!ft_strchr("01 NSWE", line[i]))
			return (PARSER_MAP_CHAR);
	content = ft_strdup(line);
	if (!content)
		return (MALLOC_STRDUP);
	elem = ft_lstnew(content);
	if (!elem)
	{
		free(content);
		return (MALLOC_LSTNEW);
	}
	ft_lstadd_back(&cub->raw_map, elem);
	return (NULL);
}

static char	*apply_colors(t_cub_file *cub, char *cat, char **colors_tab)
{
	t_vect3i	*color;

	if ((*cat == 'F' && cub->color_f.r >= 0) || (*cat == 'C'
			&& cub->color_c.r >= 0))
		return (PARSER_COLOR_ONCE);
	color = &cub->color_f;
	if (*cat == 'C')
		color = &cub->color_c;
	color->r = ft_atoi(colors_tab[0]);
	color->g = ft_atoi(colors_tab[1]);
	color->b = ft_atoi(colors_tab[2]);
	debug_print_colors(cat, *color);
	ft_free_tab(colors_tab);
	if (!ft_inrange(color->r, 0, 256) || !ft_inrange(color->g, 0, 256)
		|| !ft_inrange(color->b, 0, 256))
		return (PARSER_COLOR_RANGE);
	return (NULL);
}

char	*parse_cub_line_texture(t_cub_file *cub, char *line)
{
	t_direction	dir;

	dir = NONE;
	line = ft_skip_chars(line, ' ');
	if (!ft_strncmp(line, "NO", 2) && !cub->tex_path[NO])
		dir = NO;
	else if (!ft_strncmp(line, "SO", 2) && !cub->tex_path[SO])
		dir = SO;
	else if (!ft_strncmp(line, "WE", 2) && !cub->tex_path[WE])
		dir = WE;
	else if (!ft_strncmp(line, "EA", 2) && !cub->tex_path[EA])
		dir = EA;
	line += 2;
	line = ft_skip_chars(line, ' ');
	if (*line == 0 || dir == NONE)
		return (PARSER_TEXTURE_LINE);
	if (dir == NO)
		cub->tex_path[NO] = ft_strdup(line);
	else if (dir == SO)
		cub->tex_path[SO] = ft_strdup(line);
	else if (dir == WE)
		cub->tex_path[WE] = ft_strdup(line);
	else if (dir == EA)
		cub->tex_path[EA] = ft_strdup(line);
	return (NULL);
}

char	*parse_cub_line_color(t_cub_file *cub, char **tab)
{
	char **colors;
	int i;
	int comma;

	if (!tab[1] || tab[2])
		return (PARSER_COLOR_LINE_ELEM);
	i = -1;
	comma = 0;
	while (tab[1][++i])
	{
		if (tab[1][i] == ',')
			++comma;
		else if (!ft_isdigit(tab[1][i]))
			return (PARSER_COLOR_LINE_CHAR);
	}
	if (comma != 2 || ft_strlen(tab[1]) > 11)
		return (PARSER_COLOR_LINE_FMT);
	colors = ft_split(tab[1], ',');
	if (!colors)
		return (MALLOC_COLLINE);
	return (apply_colors(cub, tab[0], colors));
}