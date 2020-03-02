/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:30:45 by kparis            #+#    #+#             */
/*   Updated: 2020/03/02 17:06:20 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void clear(t_mlx *data)
{
	int width = 0;
	int height = 0;

	while (height < data->map->res_y)
	{
		width = 0;
		while (width < data->map->res_x)
		{
			ft_mlx_pixel_put(data->img, width, height, 0x00000000);
			width++;
		}
		height++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img->img, 0, 0);
}

void move(t_ray *ray, t_mlx *data)
{
	double old_dir_x;
	double old_plane_x;

	if (data->key->key_up == 1)
	{
		if (data->map->map[(int)(ray->pos_x + ray->dir_x * ray->movespeed)][(int)ray->pos_y] == 0)
			ray->pos_x += ray->dir_x * ray->movespeed;
		if (data->map->map[(int)ray->pos_x][(int)(ray->pos_y + ray->dir_y * ray->movespeed)] == 0)
			ray->pos_y += ray->dir_y * ray->movespeed;
	}
	if (data->key->key_down == 1)
	{
		if (data->map->map[(int)(ray->pos_x - ray->dir_x * ray->movespeed)][(int)ray->pos_y] == 0)
			ray->pos_x -= ray->dir_x * ray->movespeed;
		if (data->map->map[(int)ray->pos_x][(int)(ray->pos_y - ray->dir_y * ray->movespeed)] == 0)
			ray->pos_y -= ray->dir_y * ray->movespeed;
	}
	if (data->key->key_turnleft == 1 || data->key->key_turnright == 1)
	{
		old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(data->player->rot_speed * -1) - ray->dir_y * sin(data->player->rot_speed * -1);
		ray->dir_y = old_dir_x * sin(data->player->rot_speed * -1) + ray->dir_y * cos(data->player->rot_speed * -1);
		old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(data->player->rot_speed * -1) - ray->plane_y * sin(data->player->rot_speed * -1);
		ray->plane_y = old_plane_x * sin(data->player->rot_speed * -1) + ray->plane_y * cos(data->player->rot_speed * -1);
	}
	if (data->key->key_right)
	{
		if (data->map->map[(int)(ray->pos_x + ray->plane_x  * ray->movespeed)][(int)ray->pos_y] == 0)
			ray->pos_x += ray->plane_x * ray->movespeed;
		if (data->map->map[(int)ray->pos_x][(int)(ray->pos_y + ray->plane_y  * ray->movespeed)] == 0)
			ray->pos_y += ray->plane_y * ray->movespeed;
	}
	if (data->key->key_left)
	{
		if (data->map->map[(int)(ray->pos_x - ray->plane_x  * ray->movespeed)][(int)ray->pos_y] == 0)
			ray->pos_x -= ray->plane_x * ray->movespeed;
		if (data->map->map[(int)ray->pos_x][(int)(ray->pos_y - ray->plane_y  * ray->movespeed)] == 0)
			ray->pos_y -= ray->plane_y * ray->movespeed;
	}
}

int raycasting(t_mlx *data)
{
	t_ray ray;

	ray.pos_x = data->player->player_x;
	ray.pos_y = data->player->player_y + 0.5;
	ray.dir_x = data->player->player_dir_x;
	ray.dir_y = data->player->player_dir_y;
	ray.w = data->map->res_x;
	ray.h = data->map->res_y;
	ray.movespeed = 0.02;

	if (data->key->key_up || data->key->key_down || data->key->key_left || data->key->key_right || data->player->rot_speed)
	{
		ray.x = 0;
		ray.plane_x = 0;
		ray.plane_y = 0.66;
		clear(data);
		move(&ray, data);
		while (ray.x < ray.w)
		{
			ray.camera_x = 2 * ray.x / (double)ray.w - 1;
			ray.raydir_x = ray.dir_x + ray.plane_x * ray.camera_x;
			ray.raydir_y = ray.dir_y + ray.plane_y * ray.camera_x;

			ray.map_x = (int)ray.pos_x;
			ray.map_y = (int)ray.pos_y;
			ray.delta_dist_x = (ray.raydir_y == 0) ? 0 : ((ray.raydir_x == 0) ? 1 : fabs(1 / ray.raydir_x));
			ray.delta_dist_y = (ray.raydir_x == 0) ? 0 : ((ray.raydir_y == 0) ? 1 : fabs(1 / ray.raydir_y));
			ray.hit = 0;

			//init side distance
			if (ray.raydir_x < 0)
			{
				ray.step_x = -1;
				ray.side_dist_x = (ray.pos_x - ray.map_x) * ray.delta_dist_x;
			}
			else
			{
				ray.step_x = 1;
				ray.side_dist_x = (ray.map_x + 1.0 - ray.pos_x) * ray.delta_dist_x;
			}
			if (ray.raydir_y < 0)
			{
				ray.step_y = -1;
				ray.side_dist_y = (ray.pos_y - ray.map_y) * ray.delta_dist_y;
			}
			else
			{
				ray.step_y = 1;
				ray.side_dist_y = (ray.map_y + 1.0 - ray.pos_y) * ray.delta_dist_y;
			}
			//dda
			while (ray.hit == 0)
			{
				if (ray.side_dist_x < ray.side_dist_y)
				{
					ray.side_dist_x += ray.delta_dist_x;
					ray.map_x += ray.step_x;
					ray.side = 0;
				}
				else
				{
					ray.side_dist_y += ray.delta_dist_y;
					ray.map_y += ray.step_y;
					ray.side = 1;
				}
				if (data->map->map[ray.map_y][ray.map_x] > 0)
					ray.hit = 1;
			}
			//fisheye correction
			if (ray.side == 0)
				ray.perp_wall_dist = (ray.map_x - ray.pos_x + (1 - ray.step_x) / 2) / ray.raydir_x;
			else
				ray.perp_wall_dist = (ray.map_y - ray.pos_y + (1 - ray.step_y) / 2) / ray.raydir_y;

			//calcul ligne start et end
			ray.line_height = (int)(ray.h / ray.perp_wall_dist);
			ray.draw_start = (ray.line_height * -1) / 2 + ray.h / 2;
			if (ray.draw_start < 0)
				ray.draw_start = 0;
			ray.draw_end = ray.line_height / 2 + ray.h / 2;
			if (ray.draw_end >= ray.h)
				ray.draw_end = ray.h - 1;

			ray.color = 0x00747474;
			if (ray.side == 1)
				ray.color = 0x00545454;

			while (ray.draw_start < ray.draw_end)
			{
				ft_mlx_pixel_put(data->img, ray.x, ray.draw_start, ray.color);
				ray.draw_start++;
			}
			if (ray.draw_end < 0)
				ray.draw_end = ray.h;
			int y = ray.draw_end;
			while (y < ray.h)
			{

				ft_mlx_pixel_put(data->img, ray.x, y, 0x0021825C);// trace le pixel du sol
				ft_mlx_pixel_put(data->img, ray.x, ray.h - y - 1, 0x00a6daef);// trace le pixel du plafond
				y++;
			}
			ray.x++;
		}
		mlx_put_image_to_window(data->mlx, data->window, data->img->img, 0, 0);
		data->player->player_x = ray.pos_x;
		data->player->player_y = ray.pos_y;
		data->player->player_dir_x = ray.dir_x;
		data->player->player_dir_y = ray.dir_y;
	}
	return(1);
}
