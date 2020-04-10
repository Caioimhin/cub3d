/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 04:35:42 by kparis            #+#    #+#             */
/*   Updated: 2020/04/10 04:37:39 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_mlx *data, t_ray *ray)
{
	double old_dir_x;
	double old_plane_x;

	if (data->k_up)
	{
		if(data->map->map[(int)ray->pos_y][(int)(ray->pos_x - ray->dir_x * ray->move_speed)] == '0')
			ray->pos_x += ray->dir_x * ray->move_speed;
		if(data->map->map[(int)(ray->pos_y - ray->dir_y * ray->move_speed)][(int)ray->pos_x] == '0')
			ray->pos_y += ray->dir_y * ray->move_speed;
	}
	//move backwards if no wall behind you
	if (data->k_down)
	{
		if(data->map->map[(int)ray->pos_y][(int)(ray->pos_x - ray->dir_x * ray->move_speed)] == '0')
			ray->pos_x -= ray->dir_x * ray->move_speed;
		if(data->map->map[(int)(ray->pos_y - ray->dir_y * ray->move_speed)][(int)ray->pos_x] == '0')
			ray->pos_y -= ray->dir_y * ray->move_speed;
	}
	if (data->k_right)
	{
		if (data->map->map[(int)ray->pos_y][(int)(ray->pos_x + ray->plane_x  * ray->move_speed)] == '0')
			ray->pos_x += ray->plane_x * ray->move_speed;
		// si le prochain tile sur Y est libre on avance sur Y
		if (data->map->map[(int)(ray->pos_y + ray->plane_y * ray->move_speed)][(int)ray->pos_x] == '0') {
			ray->pos_y += ray->plane_y * ray->move_speed;
		}
	}
	// Latéral gauche
	if (data->k_left)
	{
		// si le prochain tile sur X est libre on recule sur X
		if (data->map->map[(int)ray->pos_y][(int)(ray->pos_x - ray->plane_x  * ray->move_speed)] == '0') {
			ray->pos_x -= ray->plane_x * ray->move_speed;
		}
		// si le prochain tile sur Y est libre on recule sur Y
		if (data->map->map[(int)(ray->pos_y - ray->plane_y * ray->move_speed)][(int)ray->pos_x] == '0') {
			ray->pos_y -= ray->plane_y * ray->move_speed;
		}
	}
	//rotate to the right
	if (data->k_turn_left)
	{
		//both camera direction and camera plane must be rotated
		old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-ray->rot_speed) - ray->dir_y * sin(-ray->rot_speed);
		ray->dir_y = old_dir_x * sin(-ray->rot_speed) + ray->dir_y * cos(-ray->rot_speed);
		old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-ray->rot_speed) - ray->plane_y * sin(-ray->rot_speed);
		ray->plane_y = old_plane_x * sin(-ray->rot_speed) + ray->plane_y * cos(-ray->rot_speed);
	}
	//rotate to the left
	if (data->k_turn_right)
	{
		//both camera direction and camera plane must be rotated
		old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(ray->rot_speed) - ray->dir_y * sin(ray->rot_speed);
		ray->dir_y = old_dir_x * sin(ray->rot_speed) + ray->dir_y * cos(ray->rot_speed);
		old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(ray->rot_speed) - ray->plane_y * sin(ray->rot_speed);
		ray->plane_y = old_plane_x * sin(ray->rot_speed) + ray->plane_y * cos(ray->rot_speed);
	}
}

void	init_ray(t_mlx *data, t_ray *ray)
{
	ray->init = 1;
	ray->move_speed = 0.2;
	ray->rot_speed = 0.1;
	if (data->map->dir == 'N')
	{
		ray->dir_x = 0;
		ray->dir_y = -1;
		ray->plane_x = 0.66;
		ray->plane_y = 0;
	}
	//sud
	else if (data->map->dir == 'S')
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
		ray->plane_x = -0.66;
		ray->plane_y = 0;
	}
	//Ouest
	else if (data->map->dir == 'W')
	{
		ray->dir_x = -1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = -0.66;
	}
	//Est
	else if (data->map->dir == 'E')
	{
		ray->dir_x = 1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = 0.66;
	}
}

void	dda(t_mlx *data, t_ray *ray)
{
	//perform DDA
	while (ray->hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		//Check if ray has ray->hit a wall
		if (data->map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}