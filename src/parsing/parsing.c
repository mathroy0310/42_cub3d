/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:28:24 by maroy             #+#    #+#             */
/*   Updated: 2023/10/09 02:03:47 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void init_cub_file_data(t_cub_file *cub)
{
	cub->no_tex_path = NULL;
	cub->so_tex_path = NULL;
	cub->we_tex_path = NULL;
	cub->ea_tex_path = NULL;
	cub->color_c.r = -1;
	cub->color_c.g = -1;
	cub->color_c.b = -1;
	cub->color_f.r = -1;
	cub->color_f.g = -1;
	cub->color_f.b = -1;
	cub->raw_map = NULL;
}

void	free_cub_data(t_cub_file *cub)
{
	if (!cub)
		return ;
	if (cub->no_tex_path)
		free(cub->no_tex_path);
	if (cub->so_tex_path)
		free(cub->so_tex_path);
	if (cub->we_tex_path)
		free(cub->we_tex_path);
	if (cub->ea_tex_path)
		free(cub->ea_tex_path);
	ft_lstclear(&cub->raw_map, free);
}

bool is_str_in_tab(char *str, char **tab)
{
	if (!str || !tab)
		return (false);
	while (*tab)
	{
		if (ft_strcmp(str, *tab) == 0)
			return (true);
		tab++;
	}
	return (false);
}

bool is_charset_in_str(char *str, char *charset)
{
	if (!str || !charset)
		return (false);
	if (*charset == 0)
		return (true);
	while (*charset)
		if (ft_strchr(str, *(charset++)))
			return (true);
	return (false);
}

static char *parse_cub_line(t_cub_file *cub, char *line)
{
	char **tab;
	char *error;

	tab = ft_split(line, ' ');
	if (!tab)
		error = MALLOC_SPLIT;
	else if (!tab[0])
		error = NULL;
	else if (is_str_in_tab(tab[0], (char *[]){"NO", "SO", "WE", "EA", NULL}) == true)
		error = parse_cub_line_texture(cub, line);
	else if (is_str_in_tab(tab[0], (char *[]){"F", "C", NULL}) == true)
		error = parse_cub_line_color(cub, tab);
	else if (**tab == '1')
		error = parse_cub_line_map(cub, line);
	else
		error = PARSER_LINE_FMT;
	if (error)
		free_cub_data(cub);
	ft_free_tab(tab);
	return (error);
} 



char	*parse_cub_file(t_cub_file *cub_file, int fd)
{
	char *line;
	char *error;
	
	while (true)
	{
		line = get_next_line(fd);	
		if (line == NULL)
			break;
		error = parse_cub_line(cub_file, line);
		free(line);
		if (error)
			return (error);
	}
	if (!check_file_ext(cub_file->no_tex_path, ".xpm") || \
		!check_file_ext(cub_file->so_tex_path, ".xpm") || \
		!check_file_ext(cub_file->we_tex_path, ".xpm") || \
		!check_file_ext(cub_file->ea_tex_path, ".xpm"))
		error = PARSER_XPM_EXT;
	else if (!can_read_file(cub_file->no_tex_path) || \
			 !can_read_file(cub_file->so_tex_path) || \
			 !can_read_file(cub_file->we_tex_path) || \
			 !can_read_file(cub_file->ea_tex_path))
		error = PARSER_XPM_OPN;
	if (!error)
		error = check_cub_map(make_char_map(cub_file->raw_map));
	if (error)
		free_cub_data(cub_file);
	return (error);
}

