/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:24:23 by maroy             #+#    #+#             */
/*   Updated: 2024/02/12 14:38:07 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_file_ext(char *filename, char *ext)
{
	if (!filename || !ext)
		return (false);
	if (!ft_strequal(ext, ft_strrchr(filename, '.')))
		return (false);
	return (true);
}

bool	is_charset_in_str(char *str, char *charset)
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

char	*is_valid_img_extension(t_cub_file *cub_file)
{
	int		i;
	char	*error;

	i = -1;
	while (++i < NONE)
	{
		if (!(check_file_ext(cub_file->tex_path[i], ".xpm42")
				|| check_file_ext(cub_file->tex_path[i], ".png")))
			error = PARSER_XPM_EXT;
		else if (!can_read_file(cub_file->tex_path[i]))
			error = PARSER_XPM_OPN;
		if (error)
			break ;
	}
	return (error);
}
