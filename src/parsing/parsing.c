/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:28:24 by maroy             #+#    #+#             */
/*   Updated: 2023/10/03 20:11:36 by maroy            ###   ########.fr       */
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
		//free_cub_data(cub);
	ft_free_tab(tab);
	return (error);
} 

char	*parse_cub_file(char *filename)
{
	int fd;
	char *line;
	char *error;
	t_cub_file *cub_file;
	
	cub_file = malloc(sizeof(t_cub_file));
	fd = open(filename, O_RDONLY);
	init_cub_file_data(cub_file);
	int i = 0;
	while (true)
	{
		line = get_next_line(fd);	
		if (line == NULL)
			break;
		error = parse_cub_line(cub_file, line);
		//free(line);
		i++;
	}
	printf("NO: %s\n", cub_file->no_tex_path);
	printf("SO: %s\n", cub_file->so_tex_path);
	printf("WE: %s\n", cub_file->we_tex_path);
	printf("EA: %s\n", cub_file->ea_tex_path);
	printf("F: %d, %d, %d\n", cub_file->color_f.r, cub_file->color_f.g, cub_file->color_f.b);
	printf("C: %d, %d, %d\n", cub_file->color_c.r, cub_file->color_c.g, cub_file->color_c.b);
	printf("MAP:\n");
	//free(cub_file);
	return (error);
}

