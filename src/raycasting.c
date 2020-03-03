/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:30:45 by kparis            #+#    #+#             */
/*   Updated: 2020/03/03 15:55:27 by kparis           ###   ########.fr       */
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
	mlx_put_image_to_window(data->mlx, data->window, data->img->img, 0, 0);
	return(1);
}
