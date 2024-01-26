#include "cub3d.h"
#include "parsing.h"

bool load_textures(t_cub_file *cub, t_game *game)
{
	(void)cub;
	game->xpm[NO] = mlx_load_xpm42(cub->no_tex_path);
	game->xpm[SO] = mlx_load_xpm42(cub->so_tex_path);
	game->xpm[WE] = mlx_load_xpm42(cub->we_tex_path);
	game->xpm[EA] = mlx_load_xpm42(cub->ea_tex_path);
	if (!game->xpm[NO] || !game->xpm[SO] || !game->xpm[WE] || !game->xpm[EA])
		return (false);
	
	game->textures[NO] = mlx_texture_to_image(game->mlx, &game->xpm[NO]->texture);
	game->textures[SO] = mlx_texture_to_image(game->mlx, &game->xpm[SO]->texture);
	game->textures[WE] = mlx_texture_to_image(game->mlx, &game->xpm[WE]->texture);
	game->textures[EA] = mlx_texture_to_image(game->mlx, &game->xpm[EA]->texture);

	if (!game->textures[NO] || !game->textures[SO] || !game->textures[WE] || !game->textures[EA])
		return (false);
	return (true);
}

// Calculates the x-coordinate on the texture
int get_texture_x(t_ray ray) {
    double wall_x;

    // Determine the exact position on the wall that the ray has hit
    if (ray.wall_dir == NO || ray.wall_dir == SO)
        wall_x = ray.wall_hit.x;
    else
        wall_x = ray.wall_hit.y;

    // Normalize the value to get the exact position on the texture
    wall_x -= floor(wall_x);

    // Scale the position to the texture size
    int tex_x = (int)(wall_x * (double)IMG_SIZE / 2);

    // // Ensure the texture wraps correctly
    // tex_x = tex_x % IMG_SIZE;

    return tex_x;
}
