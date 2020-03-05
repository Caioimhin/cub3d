/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:38:42 by kparis            #+#    #+#             */
/*   Updated: 2020/03/05 18:38:01 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move(t_ray *ray, t_mlx *data)
{
	if (data->key->key_up)
	{
		if(data->map->map[(int)(ray->pos_x + ray->dir_x * ray->movespeed)][(int)ray->pos_y] == 0)
			ray->pos_x += ray->dir_x * ray->movespeed;
		if(data->map->map[(int)ray->pos_x][(int)(ray->pos_y + ray->dir_y * ray->movespeed)] == 0)
			ray->pos_y += ray->dir_y * ray->movespeed;
	}
	//move backwards if no wall behind you
	if (data->key->key_down)
	{
		if(data->map->map[(int)(ray->pos_x + ray->dir_x * ray->movespeed)][(int)ray->pos_y] == 0)
			ray->pos_x -= ray->dir_x * ray->movespeed;
		if(data->map->map[(int)ray->pos_x][(int)(ray->pos_y + ray->dir_y * ray->movespeed)] == 0)
			ray->pos_y -= ray->dir_y * ray->movespeed;
	}
	if (data->key->key_right)
	{
		if (data->map->map[(int)(ray->pos_x + ray->plane_x  * ray->movespeed)][(int)ray->pos_y] == 0)
			ray->pos_x += ray->plane_x * ray->movespeed;
		if (data->map->map[(int)ray->pos_x][(int)(ray->pos_y + ray->plane_y * ray->movespeed)] == 0)
			ray->pos_y += ray->plane_y * ray->movespeed;
	}

	// Latéral gauche
	if (data->key->key_left)
	{
		if (data->map->map[(int)(ray->pos_x - ray->plane_x  * ray->movespeed)][(int)ray->pos_y] == 0)
			ray->pos_x -= ray->plane_x * ray->movespeed;
		if (data->map->map[(int)ray->pos_x][(int)(ray->pos_y - ray->plane_y * ray->movespeed)] == 0)
			ray->pos_y -= ray->plane_y * ray->movespeed;
	}
	//rotate to the right
	if (data->key->key_turnright)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(data->player->rot_speed * -1) - ray->dir_y * sin(data->player->rot_speed * -1);
		ray->dir_y = oldDirX * sin(data->player->rot_speed * -1) + ray->dir_y * cos(data->player->rot_speed * -1);
		double oldPlaneX = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(data->player->rot_speed * -1) - ray->plane_y * sin(data->player->rot_speed * -1);
		ray->plane_y = oldPlaneX * sin(data->player->rot_speed * -1) + ray->plane_y * cos(data->player->rot_speed * -1);
	}
	//rotate to the left
	if (data->key->key_turnleft)
	{
	//both camera direction and camera plane must be rotated
		double oldDirX = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(data->player->rot_speed * -1) - ray->dir_y * sin(data->player->rot_speed * -1);
		ray->dir_y = oldDirX * sin(data->player->rot_speed * -1) + ray->dir_y * cos(data->player->rot_speed * -1);
		double oldPlaneX = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(data->player->rot_speed * -1) - ray->plane_y * sin(data->player->rot_speed * -1);
		ray->plane_y = oldPlaneX * sin(data->player->rot_speed * -1) + ray->plane_y * cos(data->player->rot_speed * -1);
	}
}

void clear(t_mlx *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->map->res_y)
	{
		x = 0;
		while (x < data->map->res_x)
		{
			ft_mlx_pixel_put(data->img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img->img, 0, 0);
}

void raycasting(t_ray *ray, t_mlx *data)
{
	clear(data);
	ray->x = 0;
	while (ray->x < ray->w)
	{
		ray->camera_x = 2 * ray->x / (double)ray->w - 1;
		ray->raydir_x = ray->dir_x + ray->plane_x * ray->camera_x;
		ray->raydir_y = ray->dir_y + ray->plane_y * ray->camera_x;

		ray->map_x = (int)ray->pos_x;
		ray->map_y = (int)ray->pos_y;
		ray->delta_dist_x = (ray->raydir_y == 0) ? 0 : ((ray->raydir_x == 0) ? 1 : fabs(1/ ray->raydir_x));
		ray->delta_dist_y = (ray->raydir_x == 0) ? 0 : ((ray->raydir_y == 0) ? 1 : fabs(1/ ray->raydir_y));
		ray->hit = 0;

		if (ray->raydir_x < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
		}
		else
		{
			ray->step_x = 1;
			ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
		}
		if (ray->raydir_y < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
		}

		while (ray->hit == 0)
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;
				ray->map_x += ray->step_x;
				ray->side = 0;
			}
			else
			{
				ray->side_dist_y += ray->delta_dist_y;
				ray->map_y += ray->step_y;
				ray->side = 1;
			}
			if (data->map->map[ray->map_x][ray->map_y] > 0)
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->raydir_x;
		else
			ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->raydir_y;
		ray->line_height = (int)(ray->h / ray->perp_wall_dist);

		ray->draw_start = (ray->line_height * -1) / 2 + ray->h / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + ray->h / 2;
		if (ray->draw_end >= ray->h)
			ray->draw_end = ray->h - 1;

		ray->color = 0x00f37f2d;
		if (ray->side == 1)
			ray->color = 0x00b66125;
		while (ray->draw_start < ray->draw_end)
		{
			ft_mlx_pixel_put(data->img, ray->x, ray->draw_start, ray->color);
			ray->draw_start++;
		}

		if (ray->draw_end < 0) {
			ray->draw_end = ray->h;
		}
		//trace le sol de la fin du mur au bas de l'écran
		int y = ray->draw_end;
		while (y < ray->h) {

			ft_mlx_pixel_put(data->img, ray->x, y, data->map->floor);// trace le pixel du sol
			ft_mlx_pixel_put(data->img, ray->x, ray->h - y - 1, data->map->ceiling);// trace le pixel du plafond
			y++;
		}
		ray->x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img->img, 0, 0);
}

int loop(t_mlx *data)
{
	int update;

	update = 0;

	if (data->key->key_up || data->key->key_down || data->key->key_left || data->key->key_right || data->key->key_turnleft || data->key->key_turnright)
	{
		move(data->ray, data);
		update = 1;
	}
	if (update == 1)
		raycasting(data->ray, data);
	return (0);
}