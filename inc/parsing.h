/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:38:49 by maroy             #+#    #+#             */
/*   Updated: 2024/01/24 14:41:22 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"
# include "libft.h"

void		first_arg_checks(int argc, char **argv);
void		launch_parser(char *filename, t_cub_file *cub);
bool		is_charset_in_str(char *str, char *charset);
bool		can_read_file(char *filename);
char		*check_cub_map(char **map);
bool		check_file_ext(char *filename, char *ext);

char		*parse_cub_file(t_cub_file *cub_file, int fd);
char		*parse_cub_line_map(t_cub_file *cub, char *line);
char		*parse_cub_line_color(t_cub_file *cub, char **tab);
char		*parse_cub_line_texture(t_cub_file *cub, char *line);

void		init_cub_file_data(t_cub_file *cub);
void		free_cub_data(t_cub_file *cub);

#endif