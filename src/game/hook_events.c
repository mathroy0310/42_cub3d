

#include "cub3d.h"

void				rect(mlx_image_t *img, t_shape shape, t_color color);
void				rect_fade(mlx_image_t *img, t_shape shape, t_color color);
int 				get_texture_x(t_ray ray);

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
	t_game	*game;

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

#define max(a, b) ((a) > (b) ? (a) : (b))

void darken_color(uint32_t *color, double amount)
{
    uint8_t r, g, b, a;

    r = (*color >> 24) & 0xFF;
    g = (*color >> 16) & 0xFF;
	b = (*color >> 8) & 0xFF;
    a = *color & 0xFF;

    r = (uint8_t)max(0, r * amount);
    g = (uint8_t)max(0, g * amount);
    b = (uint8_t)max(0, b * amount);

    *color = (r << 24) | (g << 16) | (b << 8) | a;
}

// void	draw_walls(t_game *game, t_ray *rays)
// {
// 	uint32_t	i;
// 	uint32_t	x;
// 	uint32_t	y;
// 	t_color	color;

// 	int texture_x;
// 	int texture_y;

// 	i = -1;
// 	while (++i < RAYS_NB)
// 	{
// 		rays[i].wall_dist *= cos(game->p.dir - rays[i].angle_abs);
// 		rays[i].wall_height = (int32_t)(WIN_Y / rays[i].wall_dist);
// 		rays[i].draw_height = rays[i].wall_height;
// 		if (rays[i].draw_height > WIN_Y)
// 			rays[i].draw_height = WIN_Y;

// 		uint32_t top_wall = (WIN_Y - rays[i].draw_height) / 2;
// 		uint32_t bottom_wall = top_wall + rays[i].draw_height;

// 		printf("top_wall: %d\n", top_wall);
// 		printf("bottom_wall: %d\n", bottom_wall);

// 		y = -1;
// 		while (++y < WIN_Y)
// 		{
// 			//printf("y: %d\n", y);
// 			x = i * (WIN_X / RAYS_NB) - 1;
// 			texture_y = (y - top_wall) * ((float)IMG_SIZE / rays[i].draw_height);
// 			while (++x < (i + 1) * (WIN_X / RAYS_NB))
// 			{
// 				//printf("x: %d\n", x);
// 				texture_x = get_texture_x(rays[i]);
// 				if (y < top_wall)
// 				{
// 					color = game->color_c;
// 					darken_color(&color,0.2 + 0.75 *  (1 - (double)y / WIN_Y));
// 					// ft_debug_printf("color c = %u" ,color);
// 					mlx_put_pixel(game->img_screen, x, y, color);
// 				}
// 				else if (y >= top_wall && y <= bottom_wall)
// 				{
// 					// int texture_x = get_texture_x(rays[i]);
// 					// int texture_y = (y - top_wall) * ((float)IMG_SIZE / rays[i].draw_height);
// 					color = rays[i].wall_dir == NO ? game->textures[NO]->pixels[texture_y * IMG_SIZE + texture_x] : 0xFFFFFFFF;
// 					color = rays[i].wall_dir == SO ? game->textures[SO]->pixels[texture_y * IMG_SIZE + texture_x] : 0xFFFFFFFF;
// 					color = rays[i].wall_dir == WE ? game->textures[WE]->pixels[texture_y * IMG_SIZE + texture_x] : 0xFFFFFFFF;
// 					color = rays[i].wall_dir == EA ? game->textures[EA]->pixels[texture_y * IMG_SIZE + texture_x] : 0xFFFFFFFF;
// 					mlx_put_pixel(game->img_screen, x, y, color);
// 				}
// 				else
// 				{
// 					color = game->color_f;
// 					darken_color(&color,0.2 + 0.75 *( 1 - (double)(WIN_Y - 1 - y) / WIN_Y));
// 					// ft_debug_printf("color f = %u" ,color);
// 					mlx_put_pixel(game->img_screen, x, y, color);
// 				}
// 			}
// 		}
// 	}
// }

t_vect3 get_color(t_color color);

void draw_walls(t_game *game, t_ray *rays)
{
	int	i = -1;
	(void)game;
	int	x = -1;
	int	y = -1;
	t_color	color = 0xFFFFFFFF;
	
	double spacing;
	if (WIN_X % RAYS_NB == 0)
		spacing = WIN_X / RAYS_NB;
	else
		spacing = (WIN_X / RAYS_NB) + 1;
	while (++i < RAYS_NB)
	{
		rays[i].wall_dist *= cos(game->p.dir - rays[i].angle_abs);
		rays[i].wall_height = (int32_t)(WIN_Y / rays[i].wall_dist);
		rays[i].draw_height = rays[i].wall_height;
		if (rays[i].draw_height > WIN_Y)
			rays[i].draw_height = WIN_Y;

		int top_wall = (WIN_Y - rays[i].draw_height) / 2;
		int bottom_wall = top_wall + rays[i].draw_height;

		double ray_position = i * spacing;
		int start_pixel = (int)ray_position;
		int end_pixel = (int)(ray_position + spacing);
		end_pixel = end_pixel > WIN_X ? WIN_X : end_pixel;
		x = start_pixel;
		while (x < end_pixel)
		{
			//printf("x: %d\n", x);
			y = -1;
			while (++y < WIN_Y)
			{
				if (y < top_wall)
				{
					color = game->color_c;
					darken_color(&color,0.2 + 0.75 *  (1 - (double)y / WIN_Y));
					mlx_put_pixel(game->img_screen, x, y, color);
				}
				else if (y >= top_wall && y <= bottom_wall)
				{	int texture_x = get_texture_x(rays[i]);
					int texture_y = (y - top_wall) * ((float)IMG_SIZE / rays[i].draw_height);
					//printf("tx: %d\n", texture_x);
					//printf("ty: %d\n", texture_y);
					if (rays[i].wall_dir == NO)
					{
						//unsigned int line_length = game->xpm[NO]->texture.bytes_per_pixel * IMG_SIZE;
						t_vect3 color_vect;
						color_vect.r = game->xpm[NO]->texture.pixels[((texture_y / 3) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[NO]->texture.bytes_per_pixel))];
						color_vect.g = game->xpm[NO]->texture.pixels[((texture_y / 3) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[NO]->texture.bytes_per_pixel) + 1)];
						color_vect.b = game->xpm[NO]->texture.pixels[((texture_y / 3) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[NO]->texture.bytes_per_pixel) + 2)];
						int alpha = game->xpm[NO]->texture.pixels[((texture_y / 3) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[NO]->texture.bytes_per_pixel) + 3)];
						color = get_rgba(color_vect.r, color_vect.g, color_vect.b, alpha);
					}
					else if (rays[i].wall_dir == SO)
					{
						t_vect3 color_vect;
						color_vect.r = game->xpm[SO]->texture.pixels[((texture_y / 2) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[SO]->texture.bytes_per_pixel))];
						color_vect.g = game->xpm[SO]->texture.pixels[((texture_y / 2) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[SO]->texture.bytes_per_pixel) + 1)];
						color_vect.b = game->xpm[SO]->texture.pixels[((texture_y / 2) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[SO]->texture.bytes_per_pixel) + 2)];
						int alpha = game->xpm[SO]->texture.pixels[((texture_y / 2) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[SO]->texture.bytes_per_pixel) + 3)];
						color = get_rgba(color_vect.r, color_vect.g, color_vect.b, alpha);
					}
					else if (rays[i].wall_dir == WE)
					{
						t_vect3 color_vect;
						color_vect.r = game->xpm[WE]->texture.pixels[((texture_y / 3) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[WE]->texture.bytes_per_pixel))];
						color_vect.g = game->xpm[WE]->texture.pixels[((texture_y / 3) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[WE]->texture.bytes_per_pixel) + 1)];
						color_vect.b = game->xpm[WE]->texture.pixels[((texture_y / 3) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[WE]->texture.bytes_per_pixel) + 2)];
						int alpha = game->xpm[WE]->texture.pixels[((texture_y / 3) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[WE]->texture.bytes_per_pixel) + 3)];
						color = get_rgba(color_vect.r, color_vect.g, color_vect.b, alpha);
					}
					else if (rays[i].wall_dir == EA)
					{
						t_vect3 color_vect;
						color_vect.r = game->xpm[EA]->texture.pixels[((texture_y / 3) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[EA]->texture.bytes_per_pixel))];
						color_vect.g = game->xpm[EA]->texture.pixels[((texture_y / 3) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[EA]->texture.bytes_per_pixel) + 1)];
						color_vect.b = game->xpm[EA]->texture.pixels[((texture_y / 3) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[EA]->texture.bytes_per_pixel) + 2)];
						int alpha = game->xpm[EA]->texture.pixels[((texture_y / 3) * IMG_SIZE * 2 + (texture_x ) * (game->xpm[EA]->texture.bytes_per_pixel) + 3)];
						color = get_rgba(color_vect.r, color_vect.g, color_vect.b, alpha);
					}
						
					// mlx_put_pixel(game->img_screen, x, y, color);
					mlx_put_pixel(game->img_screen, x, y, color);
				}
				else
				{
					color = game->color_f;
					darken_color(&color,0.2 + 0.75 *( 1 - (double)(WIN_Y - 1 - y) / WIN_Y));
					mlx_put_pixel(game->img_screen, x, y, color);
				}
			}
			++x;
		}
		//printf("i: %d\n", i);
	}
}

// void	draw_walls(t_game *game, t_ray *rays)
// {
// 	uint32_t	i;
// 	uint32_t	j;
// 	uint32_t	slice_height;
// 	//uint32_t	wall_height = 0;
// 	uint32_t	wall_top;
// 	uint32_t	wall_bottom;
// 	uint32_t	wall_color;
// 	uint32_t	ratio;
// 	uint32_t	wall_dist;
// 	t_shape		shape;

// 	(void)wall_dist;
// 	i = 0;
// 	j = 0;
// 	while (i < WIN_X)
// 	{
// 		//wall_height = rays[i].wall_dist * cos(rays[i].angle_rel- game->p.dir);
// 		if (j == i)
// 		{
// 			if (WIN_X % RAYS_NB == 0)
// 				ratio = WIN_X / RAYS_NB;
// 			else
// 				ratio = (WIN_X / RAYS_NB) + 1;
// 			j += ratio;
// 			// printf("j: %d\n", j);
// 			// printf("WIN_X: %d\n", WIN_X);
// 			// printf("WIN_Y: %d\n", WIN_Y);
// 			// printf("rays[i].wall_dist: %lf\n", rays[i].wall_dist);
// 			// printf("WIN_X / rays[%d].wall_dist: %lf\n", WIN_X / RAYS_NB,WIN_X / rays[i].wall_dist);
// 			// printf("game->img_screen->width: %d\n", game->img_screen->width);
// 			// printf("game->img_screen->height: %d\n",game->img_screen->height);
// 			wall_dist = rays[i].wall_dist * cos(rays[i].angle_rel- game->p.dir);
// 			slice_height = (uint32_t)(WIN_X / rays[i].wall_dist);
// 			wall_top = (WIN_Y / 2) - (slice_height / 2);
// 			wall_bottom = (WIN_Y / 2) + (slice_height / 2);
// 			wall_color = rays[i].wall_dir == EA ? 0x0d1b2aFF : 0xFFFFFFFF;
// 			wall_color = rays[i].wall_dir == SO ? 0x1b263bFF : 0xFFFFFFFF;
// 			wall_color = rays[i].wall_dir == WE ? 0x415a77FF : 0xFFFFFFFF;
// 			wall_color = rays[i].wall_dir == EA ? 0xc0c0c0FF : 0xFFFFFFFF;
// 			shape.x = wall_top;
// 			if ((int)shape.x < 0)
// 				shape.x = 0;
// 			shape.width = wall_bottom - wall_top;
// 			shape.y = i * (ratio);
// 			shape.height = (ratio) * (ratio);
// 			rect(game->img_screen, shape, wall_color);
// 			// printf("wall_height: %d\n", wall_height);
// 			// printf("wall_top: %d\n", wall_top);
// 			// printf("wall_bottom: %d\n", wall_bottom);
// 			// printf("wall_color: %x\n", wall_color);
// 			// printf("rays[i].wall_dir: %d\n", rays[i].wall_dir);
// 			// printf("shape.x: %d\n", shape.x);
// 			// printf("shape.y: %d\n", shape.y);
// 			// printf("shape.width: %d\n", shape.width);
// 			// printf("shape.height: %d\n", shape.height);
// 			// printf("< ---------------------- >\n");
// 		}
// 		// shape.y = 0;
// 		// shape.height = wall_top;
// 		// rect(game->img_screen, shape, game->color_c);
// 		// shape.y = wall_bottom;
// 		// shape.height = WIN_X - wall_bottom;
// 		// rect(game->img_screen, shape, game->color_f);
// 		++i;
// 	}
// }

void	my_loop(void *param)
{
	static t_ray rays[RAYS_NB];
	t_game *game;

	game = param;
	if (!is_player_moving(&game->p))
		return ;
	update_player(game);
	if (DEBUG_MODE)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: game->p.pos.y --> -={%lf }=-\n", game->p.pos.y);
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: game->p.pos.x --> -={%lf }=-\n", game->p.pos.x);
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: game->p.dir --> -={ %lf }=-\n",game->p.dir);
	}
	mlx_delete_image(game->mlx, game->img_screen);
	game->img_screen = mlx_new_image(game->mlx, WIN_X, WIN_Y);
	ray_casting(game, rays);
	//draw_floor_ceiling(game);
	draw_walls(game, rays);
	draw_minimap(game, rays);
	mlx_image_to_window(game->mlx, game->img_screen, 0, 0);
}
