/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:40:08 by maroy             #+#    #+#             */
/*   Updated: 2024/01/24 15:36:50 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	launch_parser(char *filename, t_cub_file *cub)
{
	int		fd;
	char	*error;

	fd = open(filename, O_RDONLY);
	init_cub_file_data(cub);
	error = parse_cub_file(cub, fd);
	close(fd);
	if (error)
		print_error_then_exit(filename, error);
}

bool	check_file_ext(char *filename, char *ext)
{
	if (!filename || !ext)
		return (false);
	if (!ft_strequal(ft_strrchr(filename, '.'), ext))
		return (false);
	return (true);
}

char	*check_cub_map(char **map)
{
	int		size;
	char	dir;
	int		i;

	if (!map || !(*map))
		return (CUBMAP_NULL);
	size = 0;
	while (map[size])
		size++;
	dir = 0;
	i = -1;
	while (++i < size)
		if (((i == 0 || i == size - 1) && is_charset_in_str(map[i], "0NSWE"))
			|| !is_mid_row_valid(map, i, &dir))
			break ;
	ft_free_tab(map);
	if (i != size)
		return (CUBMAP_ROW_INV);
	if (!dir)
		return (CUBMAP_DEF_DIR);
	return (NULL);
}

bool	can_read_file(char *filename)
{
	int		fd;
	long	br;
	char	c;

	if (!filename)
		return (false);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (false);
	br = read(fd, &c, 1);
	close(fd);
	return (br == 1);
}

void	first_arg_checks(int argc, char **argv)
{
	if (argc != 2)
		print_error_then_exit(NULL, PARSER_ARG_NB);
	if (!check_file_ext(argv[1], ".cub"))
		print_error_then_exit(argv[1], PARSER_ARG_EXT);
	if (!can_read_file(argv[1]))
		print_error_then_exit(argv[1], PARSER_ARG_OPEN);
}