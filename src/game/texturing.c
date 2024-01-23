#include "cub3d.h"

bool load_textures(t_game *game)
{
	game->xpm[NO] = mlx_load_xpm42(TEXTURE_NO);
	game->xpm[SO] = mlx_load_xpm42(TEXTURE_SO);
	game->xpm[WE] = mlx_load_xpm42(TEXTURE_WE);
	game->xpm[EA] = mlx_load_xpm42(TEXTURE_SO);
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
	int texture_x;
	if (ray.wall_dir == NO || ray.wall_dir == SO)
		texture_x = (int)(ray.wall_hit.x * IMG_SIZE) % IMG_SIZE;
	else
		texture_x = (int)(ray.wall_hit.y * IMG_SIZE) % IMG_SIZE;
	return (texture_x);
}
