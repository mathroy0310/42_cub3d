/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:35:37 by maroy             #+#    #+#             */
/*   Updated: 2024/01/18 11:48:11 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_line_equation(t_vect2d *pt, double angle, t_vect3d *line)
{
	if (cos(angle) == 0.0)
	{
		line->x = 1.0;
		line->y = 0.0;
		line->z = -pt->x;
		return ;
	}
	line->x = tan(angle);
	line->y = -1.0;
	line->z = pt->y - line->x * pt->x;
}

static double	distance_points(t_vect2d *p1, t_vect2d *p2)
{
	return (sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2)));
}

static double	get_intersect(t_vect3d *line, double value, bool is_h)
{
	if ((is_h && line->x == 0.0) || (!is_h && line->y == 0.0))
		return (INFINITY);
	if (is_h)
		return ((line->z + line->y * value) / (-line->x));
	return ((line->z + line->x * value) / (-line->y));
}

static double	get_min_dist_h(t_ray *ray, t_game *game, t_vect3d *line,
		t_vect2d *end)
{
	double	di;
	double	y;
	double	x;

	y = 0.0;
	x = 0.0;
	if (line->x == 0.0)
		return (INFINITY);
	di = (sin(ray->angle_abs) > 0) - (sin(ray->angle_abs) < 0);
	y = (double)((int)(game->p.pos.y) + (di == 1.0));
	while (0.0 <= y && y < (double)(game->map_h))
	{
		x = get_intersect(line, y, true);
		if (x < 0 || x >= (double)(game->map_w) || game->map[(int)y - (di ==
				-1.0)][(int)x] != '0')
			break ;
		y += di;
	}
	end->x = x;
	end->y = y;
	return (distance_points(&game->p.pos, end));
}

static double	get_min_dist_w(t_ray *ray, t_game *game, t_vect3d *line,
		t_vect2d *end)
{
	double	di;
	double	x;
	double	y;

	x = 0.0;
	y = 0.0;
	if (line->y == 0.0)
		return (INFINITY);
	di = (cos(ray->angle_abs) > 0) - (cos(ray->angle_abs) < 0);
	x = (double)((int)game->p.pos.x + (di == 1.0));
	while (0.0 <= x && x < (double)(game->map_w))
	{
		y = get_intersect(line, x, false);
		if (y < 0 || y >= (double)(game->map_h) || game->map[(int)y][(int)x
			- (di == -1.0)] != '0')
			break ;
		x += di;
	}
	end->x = x;
	end->y = y;
	return (distance_points(&game->p.pos, end));
}

void	calcul_ray(t_game *game, t_ray *ray)
{
	t_vect3d	line;
	t_vect2d	min_dist;
	t_vect2d	end_w;
	t_vect2d	end_h;
	bool		is_no_or_we;

	get_line_equation(&game->p.pos, ray->angle_abs, &line);
	min_dist.x = get_min_dist_w(ray, game, &line, &end_w);
	min_dist.y = get_min_dist_h(ray, game, &line, &end_h);
	if (min_dist.x >= min_dist.y)
	{
		is_no_or_we = game->p.pos.y < end_h.y;
		ray->wall_dist = min_dist.y;
		ray->wall_dir = (is_no_or_we)*NO + (!is_no_or_we) * SO;
		ft_memcpy(&ray->wall_hit, &end_h, sizeof(t_vect2d));
	}
	else
	{
		is_no_or_we = game->p.pos.x < end_w.x;
		ray->wall_dist = min_dist.x;
		ray->wall_dir = (is_no_or_we)*WE + (!is_no_or_we) * EA;
		ft_memcpy(&ray->wall_hit, &end_w, sizeof(t_vect2d));
	}
}

void	ray_casting(t_game *game, t_ray *rays)
{
	static bool is_first_init = false;
	int i;

	i = -1;
	if (!is_first_init)
	{
		while (++i < RAYS_NB)
		{
			rays[i].angle_rel = -PLAYER_FOV * 0.5 + (double)i * (PLAYER_FOV
					/ (double)RAYS_NB);
			rays[i].angle_abs = 0.0;
			rays[i].wall_dist = 0.0;
			rays[i].wall_dir = NONE;
			rays[i].wall_hit.x = 0.0;
			rays[i].wall_hit.y = 0.0;
		}
		is_first_init = true;
	}
	i = -1;
	while (++i < RAYS_NB)
	{
		rays[i].angle_abs = game->p.dir + rays[i].angle_rel;
		calcul_ray(game, &rays[i]);
		debug_print_ray(&rays[i], i);
	}
}