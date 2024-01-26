#include "cub3d.h"

char *load_textures(t_cub_file *cub, t_game *game)
{
	xpm_t *xpm[NONE];

	int i;

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

int get_texture_x(t_ray ray)
{
	int texture_x;
	if (ray.wall_dir == NO || ray.wall_dir == SO)
		texture_x = (int)(ray.wall_hit.x * IMG_SIZE) % IMG_SIZE;
	else
		texture_x = (int)(ray.wall_hit.y * IMG_SIZE) % IMG_SIZE;
	return (texture_x);
}
