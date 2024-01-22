

#include "cub3d.h"

void		rect(mlx_image_t *img, t_shape shape, t_color color);
void	rect_fade(mlx_image_t *img, t_shape shape, t_color color);

static void	on_key_press(mlx_key_data_t keydata, t_game *game)
{
	keys_t	key;

	key = keydata.key;
	if (key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		destroy_game(game, true);
	else if (key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->p.rotate_l = true;
	else if (key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->p.rotate_r = true;
	else if (key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->p.move_no = true;
	else if (key == MLX_KEY_S && keydata.action == MLX_PRESS)
		game->p.move_so = true;
	else if (key == MLX_KEY_A && keydata.action == MLX_PRESS)
		game->p.move_we = true;
	else if (key == MLX_KEY_D && keydata.action == MLX_PRESS)
		game->p.move_ea = true;
}

static void	on_key_release(mlx_key_data_t keydata, t_game *game)
{
	keys_t	key;

	key = keydata.key;
	if (key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->p.rotate_l = false;
	else if (key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->p.rotate_r = false;
	else if (key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		game->p.move_no = false;
	else if (key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		game->p.move_so = false;
	else if (key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		game->p.move_we = false;
	else if (key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		game->p.move_ea = false;
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = param;
	on_key_press(keydata, game);
	on_key_release(keydata, game);
}

static inline bool	is_player_moving(t_player *p)
{
	static bool	first_run = true;

	if (first_run)
	{
		first_run = false;
		return (true);
	}
	return (p->move_no || p->move_so || p->move_we || p->move_ea || p->rotate_l
		|| p->rotate_r);
}

void	draw_floor_ceiling(t_game *game)
{
	t_shape	shape;
	
	shape.x = 0;
	shape.y = 0;
	shape.width = WIN_Y / 2;
	shape.height = WIN_X;
	rect_fade(game->img_screen, shape, game->color_c);
	shape.x = WIN_Y / 2;
	rect_fade(game->img_screen, shape, game->color_f);
}

void	draw_walls(t_game *game, t_ray *rays)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	slice_height;
	uint32_t	wall_height = 0;
	uint32_t	wall_top;
	uint32_t	wall_bottom;
	uint32_t	wall_color;
	uint32_t	ratio;
	uint32_t	wall_dist;
	t_shape		shape;
	
	i = 0;
	j = 0;
	while (i < WIN_X)
	{
		//wall_height = rays[i].wall_dist * cos(rays[i].angle_rel - game->p.dir);
		if (j == i)
		{
			if (WIN_X % RAYS_NB == 0)
				ratio = WIN_X / RAYS_NB;
			else
				ratio = (WIN_X / RAYS_NB) + 1;
			j += ratio;
			printf("j: %d\n", j);
			printf("WIN_X: %d\n", WIN_X);
			printf("WIN_Y: %d\n", WIN_Y);
			printf("rays[i].wall_dist: %lf\n", rays[i].wall_dist);
			printf("WIN_X / rays[%d].wall_dist: %lf\n", WIN_X / RAYS_NB, WIN_X / rays[i].wall_dist);
			printf("game->img_screen->width: %d\n", game->img_screen->width);
			printf("game->img_screen->height: %d\n", game->img_screen->height);
			wall_dist = rays[i].wall_dist * cos(rays[i].angle_rel - game->p.dir);
			slice_height = (uint32_t)(WIN_X / rays[i].wall_dist);
			wall_top = (WIN_Y / 2) - (slice_height / 2);
			wall_bottom = (WIN_Y / 2) + (slice_height / 2);
			wall_color = rays[i].wall_dir == NO ? 0x0d1b2aFF : 0xFFFFFFFF;
			wall_color = rays[i].wall_dir == SO ? 0x1b263bFF : 0xFFFFFFFF;
			wall_color = rays[i].wall_dir == WE ? 0x415a77FF : 0xFFFFFFFF;
			wall_color = rays[i].wall_dir == EA ? 0xc0c0c0FF : 0xFFFFFFFF;
			shape.x = wall_top;
			if ((int)shape.x < 0)
				shape.x = 0;
			shape.width = wall_bottom - wall_top;
			shape.y = i * (ratio);
			shape.height = (ratio) * (ratio);
			rect(game->img_screen, shape, wall_color);
			printf("wall_height: %d\n", wall_height);
			printf("wall_top: %d\n", wall_top);
			printf("wall_bottom: %d\n", wall_bottom);
			printf("wall_color: %x\n", wall_color);
			printf("rays[i].wall_dir: %d\n", rays[i].wall_dir);
			printf("shape.x: %d\n", shape.x);
			printf("shape.y: %d\n", shape.y);
			printf("shape.width: %d\n", shape.width);
			printf("shape.height: %d\n", shape.height);
			printf("< ---------------------- >\n");
		}
		// shape.y = 0;
		// shape.height = wall_top;
		// rect(game->img_screen, shape, game->color_c);
		// shape.y = wall_bottom;
		// shape.height = WIN_X - wall_bottom;
		// rect(game->img_screen, shape, game->color_f);
		++i;
	}
}

void	my_loop(void *param)
{
	static t_ray	rays[RAYS_NB];
	t_game	*game;
	
	game = param;
	if (!is_player_moving(&game->p))
		return ;
	update_player(game);
	if (DEBUG_MODE)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE"DEBUG 🐞: game->p.pos.y --> -={ %lf }=-\n", game->p.pos.y);
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: game->p.pos.x --> -={ %lf }=-\n", game->p.pos.x);
		printf(ANSI_COLOR_BRIGHT_BLUE"DEBUG 🐞: game->p.dir --> -={ %lf }=-\n", game->p.dir);
	}
	mlx_delete_image(game->mlx, game->img_screen);
	game->img_screen = mlx_new_image(game->mlx, WIN_X, WIN_Y);
	ray_casting(game, rays);
	draw_floor_ceiling(game);
	draw_walls(game, rays);
	draw_minimap(game, rays);
	mlx_image_to_window(game->mlx, game->img_screen, 0, 0);
}