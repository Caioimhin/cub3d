/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:57:38 by kparis            #+#    #+#             */
/*   Updated: 2020/05/19 16:36:38 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		render_next_frame(t_data *data)
{
	int		x;
	t_img	*text_img;

	x = 0;
	while (x < data->maps.win_size.x)
	{
		set_ray(data, &data->ray, x);
		perform_dda(data, &data->ray);
		data->ray.z_buffer[x] = data->ray.perp_wall_dist;
		set_drawing_limits(data, &data->ray);
		text_img = get_texture_img(&data->ray);
		draw_column(data, &data->ray, text_img, x);
		x++;
	}
	sort_sprites(&data->maps, &data->ray);
	draw_sprites(data, &data->maps, &data->ray, &data->ray.S_img);
	if (data->save == 1)
		create_bmp(data, &data->img, "start.bmp");
	mlx_put_image_to_window(data->mlx, data->window, data->img.ptr, 0, 0);
	return (0);
}

void	draw_column(t_data *data, t_ray *ray, t_img *text_img, int x)
{
	t_int	pos;
	double	step;
	double	tex_pos;

	pos.x = x;
	pos.y = 0;
	while (pos.y < ray->draw_start)
	{
		put_pixel(&data->img, pos, data->maps.ceiling_color);
		pos.y++;
	}
	step = 1.0 * text_img->size.y / ray->line_height;
	tex_pos = (ray->draw_start - data->maps.win_size.y / 2 +
		ray->line_height / 2) * step;
	while (pos.y < ray->draw_end)
	{
		ray->text.y = (int)tex_pos & (text_img->size.y - 1);
		tex_pos += step;
		put_pixel(&data->img, pos, text_img->colors
			[(text_img->size.y * ray->text.y + ray->text.x)]);
		pos.y++;
	}
	pos.y--;
	while (pos.y++ < data->maps.win_size.y)
		put_pixel(&data->img, pos, data->maps.floor_color);
}

void	set_drawing_limits(t_data *data, t_ray *ray)
{
	ray->line_height =
		abs((int)(data->maps.win_size.y / (ray->perp_wall_dist)));
	ray->draw_start = -ray->line_height / 2 + data->maps.win_size.y / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->maps.win_size.y / 2;
	if (ray->draw_end >= data->maps.win_size.y)
		ray->draw_end = data->maps.win_size.y;
	if (ray->side == 0)
		ray->wall_x = ray->pos.y + ray->perp_wall_dist * ray->ray.y;
	else
		ray->wall_x = ray->pos.x + ray->perp_wall_dist * ray->ray.x;
	ray->wall_x -= floor((ray->wall_x));
}

void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (data->maps.map[(int)ray->map.y][(int)ray->map.x] == '1')
			hit = 1;
	}
	ray->perp_wall_dist = (ray->side == 0) ?
		(ray->map.x - ray->pos.x + (1 - ray->step.x) / 2) / ray->ray.x :
		(ray->map.y - ray->pos.y + (1 - ray->step.y) / 2) / ray->ray.y;
}

void	set_ray(t_data *data, t_ray *ray, int x)
{
	ray->map.x = (int)ray->pos.x;
	ray->map.y = (int)ray->pos.y;
	ray->camera_x = 2 * x / (double)data->maps.win_size.x - 1;
	ray->ray.x = ray->dir.x + ray->plane.x * ray->camera_x;
	ray->ray.y = ray->dir.y + ray->plane.y * ray->camera_x;
	if (ray->ray.y == 0)
		ray->delta_dist.x = 0;
	else
		ray->delta_dist.x = (ray->ray.x == 0) ? 1 : fabs(1 / ray->ray.x);
	if (ray->ray.x == 0)
		ray->delta_dist.y = 0;
	else
		ray->delta_dist.y = (ray->ray.y == 0) ? 1 : fabs(1 / ray->ray.y);
	ray->step.x = (ray->ray.x < 0) ? -1 : 1;
	ray->step.y = (ray->ray.y < 0) ? -1 : 1;
	if (ray->ray.x < 0)
		ray->side_dist.x = (ray->pos.x - ray->map.x) * ray->delta_dist.x;
	else
		ray->side_dist.x = (ray->map.x + 1.0 - ray->pos.x) * ray->delta_dist.x;
	if (ray->ray.y < 0)
		ray->side_dist.y = (ray->pos.y - ray->map.y) * ray->delta_dist.y;
	else
		ray->side_dist.y = (ray->map.y + 1.0 - ray->pos.y) * ray->delta_dist.y;
}
