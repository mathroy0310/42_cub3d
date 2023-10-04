/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:40:08 by maroy             #+#    #+#             */
/*   Updated: 2023/10/03 17:25:00 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool is_cub_file(char *filename)
{
    const char *extension = ft_strrchr(filename, '.');
    if (extension && !ft_strcmp(extension, ".cub"))
        return (true);
    print_error("Invalid file extension");
    return (false);
}

static bool is_valid_file(char *filename)
{
	int32_t fd;
	unsigned char	c;
	int64_t	br;

	fd = open(filename, O_RDONLY); 
	br = read(fd, &c, 1);
	close(fd);
	if (fd >= 0 && br == 1)
		return (true);
	print_error("Unable to read file or is empty");
	return (false);
}

bool is_valid_arg(int argc, char *argv[])
{
	if (argc != 2)
	{
		print_error("Invalid arguments");
		return (false);
	}
	if (!is_valid_file(argv[1]) || !is_cub_file(argv[1]))
		return (false);
	return (true);
}