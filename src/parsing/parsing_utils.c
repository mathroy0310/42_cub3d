/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:12:41 by maroy             #+#    #+#             */
/*   Updated: 2023/10/03 20:16:49 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static inline bool	ready_to_parse_map(t_cub_file *cub)
{
	return (cub->no_tex_path && cub->so_tex_path && cub->we_tex_path && cub->ea_tex_path
			&& cub->color_f.r >= 0 && cub->color_f.g >= 0 && cub->color_f.b >= 0
		&& cub->color_c.r >= 0 && cub->color_c.g >= 0 && cub->color_c.b >= 0);
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

static inline char	*apply_colors(t_cub_file *cub, char *cat, char **colors_tab)
{
	t_vectu3 *color;

	if ((*cat == 'F' && cub->color_f.r >= 0) || (*cat == 'C' && cub->color_c.r >= 0))
		return (PARSER_COLOR_ONCE);
	color = &cub->color_f;
	if (*cat == 'C')
		color = &cub->color_c;
	color->r = ft_atoi(colors_tab[0]);
	color->g = ft_atoi(colors_tab[1]);
	color->b = ft_atoi(colors_tab[2]);
	printf("color.r = %d\n", color->r);
	printf("color.g = %d\n", color->g);
	printf("color.b = %d\n", color->b);
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
	if (!ft_strncmp(line, "NO", 2) && !cub->no_tex_path)
		dir = NO;
	else if (!ft_strncmp(line, "SO", 2) && !cub->so_tex_path)
		dir = SO;
	else if (!ft_strncmp(line, "WE", 2) && !cub->we_tex_path)
		dir = WE;
	else if (!ft_strncmp(line, "EA", 2) && !cub->ea_tex_path)
		dir = EA;
	line += 2;
	line = ft_skip_chars(line, ' ');
	if (*line == 0 || dir == NONE)
		return (PARSER_TEXTURE_LINE);
	if (dir == NO)
		cub->no_tex_path = ft_strdup(line);
	else if (dir == SO)
		cub->so_tex_path = ft_strdup(line);
	else if (dir == WE)
		cub->we_tex_path = ft_strdup(line);
	else if (dir == EA)
		cub->ea_tex_path = ft_strdup(line);
	return (NULL);
}

char	*parse_cub_line_color(t_cub_file *cub, char **tab)
{
	char	**colors;
	int		i;
	int		comma;

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
	printf("colors[0] = %s\n", colors[0]);
	printf("colors[1] = %s\n", colors[1]);
	printf("colors[2] = %s\n", colors[2]);
	return (apply_colors(cub, tab[0], colors));
}