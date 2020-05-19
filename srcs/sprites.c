/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:58:48 by kparis            #+#    #+#             */
/*   Updated: 2020/05/19 16:49:34 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite_column(t_data *data, t_ray *ray, t_img *img, int stripe)
{
	t_int	spr_img_pos;
	t_maps	*map;
	int		d;

	spr_img_pos.x = stripe;
	spr_img_pos.y = ray->spr_draw_start.y;
	map = &data->maps;
	ray->text.x = (int)(256 * fabs(stripe - (-ray->spr_size.x / 2
		+ ray->spr_screen_x)) * img->size.x / ray->spr_size.x) / 256;
	if (ray->spr_inv.y > 0 && stripe >= 0 && stripe < map->win_size.x
		&& ray->spr_inv.y < ray->z_buffer[stripe])
	{
		while (spr_img_pos.y < ray->spr_draw_end.y)
		{
			d = (spr_img_pos.y)
				* 256 - map->win_size.y * 128 + ray->spr_size.y * 128;
			ray->text.y = ((d * img->size.y) / ray->spr_size.y) / 256;
			if ((img->colors
				[(img->size.y * ray->text.y + ray->text.x)] & 0x00FFFFFF) != 0)
				put_pixel(&data->img, spr_img_pos,
					img->colors[(img->size.y * ray->text.y + ray->text.x)]);
			spr_img_pos.y++;
		}
	}
}

void	set_sprite_drawing_limits(t_maps *map, t_ray *ray, int i)
{
	double	inv;
	t_coord	spr_diff;

	spr_diff.x = map->spr_x[i] - ray->pos.x;
	spr_diff.y = map->spr_y[i] - ray->pos.y;
	inv = 1.0 / (ray->plane.x * ray->dir.y - ray->dir.x * ray->plane.y);
	ray->spr_inv.x = inv * (ray->dir.y * spr_diff.x - ray->dir.x * spr_diff.y);
	ray->spr_inv.y = inv *
		(ray->plane.x * spr_diff.y - ray->plane.y * spr_diff.x);
	ray->spr_screen_x =
		((map->win_size.x / 2) * (1 + ray->spr_inv.x / ray->spr_inv.y));
	ray->spr_size.y = abs((int)(map->win_size.y / (ray->spr_inv.y)));
	ray->spr_draw_start.y = -ray->spr_size.y / 2 + map->win_size.y / 2;
	if (ray->spr_draw_start.y < 0)
		ray->spr_draw_start.y = 0;
	ray->spr_draw_end.y = ray->spr_size.y / 2 + map->win_size.y / 2;
	if (ray->spr_draw_end.y >= map->win_size.y)
		ray->spr_draw_end.y = map->win_size.y;
	ray->spr_size.x = abs((int)(map->win_size.y / (ray->spr_inv.y)));
	ray->spr_draw_start.x = -ray->spr_size.x / 2 + ray->spr_screen_x - 1;
	if (ray->spr_draw_start.x < 0)
		ray->spr_draw_start.x = 0;
	ray->spr_draw_end.x = ray->spr_size.x / 2 + ray->spr_screen_x + 1;
	if (ray->spr_draw_end.x > map->win_size.x)
		ray->spr_draw_end.x = map->win_size.x;
}

void	draw_sprites(t_data *data, t_maps *map, t_ray *ray, t_img *text)
{
	int	i;
	int	j;
	int	stripe;

	i = 0;
	j = 0;
	while (i < map->spr_count || j < map->spr_count)
	{
		if (j == ray->spr_order[i] && ray->spr_dist[i] > 0.1)
		{
			set_sprite_drawing_limits(map, ray, i);
			stripe = ray->spr_draw_start.x;
			while (stripe < ray->spr_draw_end.x)
			{
				draw_sprite_column(data, ray, text, stripe);
				stripe++;
			}
			j++;
			i = -1;
		}
		i++;
	}
}

void	init_sprite_order(t_maps *map, t_ray *ray)
{
	int i;

	i = 0;
	while (i < map->spr_count && !ray->spr_sorted)
	{
		ray->spr_order[i] = i;
		ray->spr_dist[i] =
			((ray->pos.x - map->spr_x[i]) * (ray->pos.x - map->spr_x[i])
			+ (ray->pos.y - map->spr_y[i]) * (ray->pos.y - map->spr_y[i]));
		i++;
	}
}

void	sort_sprites(t_maps *maps, t_ray *ray)
{
	t_int	at;
	int		tmp_order;

	init_sprite_order(maps, ray);
	at.x = 0;
	while (at.x < maps->spr_count - 1)
	{
		at.z = 0;
		at.y = at.x;
		while (++at.y < maps->spr_count)
		{
			if ((ray->spr_dist[at.x] < ray->spr_dist[at.y]
				&& ray->spr_order[at.x] < ray->spr_order[at.y])
				|| (ray->spr_dist[at.x] > ray->spr_dist[at.y]
				&& ray->spr_order[at.x] > ray->spr_order[at.y]))
			{
				at.z++;
				tmp_order = ray->spr_order[at.x];
				ray->spr_order[at.x] = ray->spr_order[at.y];
				ray->spr_order[at.y] = tmp_order;
			}
		}
		at.x = (at.z == 0) ? at.x + 1 : at.x;
	}
	ray->spr_sorted++;
}
