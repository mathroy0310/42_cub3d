/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:10:51 by maroy             #+#    #+#             */
/*   Updated: 2024/02/12 15:10:52 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*load_textures(t_cub_file *cub, t_game *game)
{
	xpm_t	*xpm[NONE];
	int		i;

	i = -1;
	while (++i < NONE)
	{
		if (check_file_ext(cub->tex_path[i], ".xpm42"))
		{
			xpm[i] = mlx_load_xpm42(cub->tex_path[i]);
			if (!xpm[i])
				return (XMP_LOAD);
			game->textures[i] = &xpm[i]->texture;
		}
		else
		{
			game->textures[i] = mlx_load_png(cub->tex_path[i]);
			if (!game->textures[i])
				return (TEX_LOAD);
		}
	}
	return (NULL);
}
