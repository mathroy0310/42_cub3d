/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:38:49 by maroy             #+#    #+#             */
/*   Updated: 2024/02/12 14:36:03 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"
# include "libft.h"

/*-- valid_utils --*/
char	*is_valid_img_extension(t_cub_file *cub_file);
bool	check_file_ext(char *filename, char *ext);
bool	is_charset_in_str(char *str, char *charset);

/*-- valid --*/
void	launch_parser(char *filename, t_cub_file *cub);
char	*check_cub_map(char **map);
void	first_arg_checks(int argc, char **argv);
bool	can_read_file(char *filename);

/*-- parsing --*/
char	*parse_cub_file(t_cub_file *cub_file, int fd);
char	*parse_cub_line_map(t_cub_file *cub, char *line);
void	init_cub_file_data(t_cub_file *cub);
void	free_cub_data(t_cub_file *cub);

/*-- parsing utils --*/
char	*parse_cub_line_color(t_cub_file *cub, char **tab);
char	*parse_cub_line_texture(t_cub_file *cub, char *line);

#endif
