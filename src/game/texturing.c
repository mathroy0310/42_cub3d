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

int get_texture_x(t_ray ray)
{
    double wall_x;

    // Determine the exact point on the wall where the ray hit
    if (ray.wall_dir == NO || ray.wall_dir == SO)
        wall_x = ray.wall_hit.x;
    else // for WE or EA
        wall_x = ray.wall_hit.y;

    // Normalize wall_x to get the exact fractional part
    wall_x -= floor(wall_x);

    // Convert this fractional part to a texture coordinate
    int tex_x = (int)(wall_x * (double)IMG_SIZE);

    // Adjust texture coordinate based on the wall direction if necessary
    // For instance, if the wall direction is North or West, you might need to invert the texture
    if (ray.wall_dir == NO || ray.wall_dir == WE)
        tex_x = IMG_SIZE - tex_x - 1;

    // Ensure tex_x is within the texture bounds
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= IMG_SIZE)
        tex_x = IMG_SIZE - 1;

    return tex_x;
}
