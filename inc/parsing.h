/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:38:49 by maroy             #+#    #+#             */
/*   Updated: 2023/10/03 19:44:44 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include"cub3d.h"
#include<stdbool.h>
#include<stdint.h>
# include "../libs/libft/inc/libft.h"

typedef struct vecti3
{
	int16_t r;
	int16_t g;
	int16_t b;
}	t_vectu3;

typedef struct s_cub_file
{
	char	*no_tex_path;
	char	*so_tex_path;
	char	*we_tex_path;
	char	*ea_tex_path;
	t_vectu3	color_f;
	t_vectu3	color_c;
	t_list	*raw_map;
}	t_cub_file;


bool is_valid_arg(int argc, char *argv[]);

char	*parse_cub_file(char *filename);
char	*parse_cub_line_map(t_cub_file *cub, char *line);
char	*parse_cub_line_color(t_cub_file *cub, char **tab);
char	*parse_cub_line_texture(t_cub_file *cub, char *line);

#endif