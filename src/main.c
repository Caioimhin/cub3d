/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:31:57 by kparis            #+#    #+#             */
/*   Updated: 2020/03/03 18:28:18 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include <fcntl.h>

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
	data->ray->x = 0;
	data->ray->plane_x = 0;
	data->ray->plane_y = 0.66;
	clear(data);
	while (data->ray->x < data->ray->w)
	{
		data->ray->camera_x = 2 * data->ray->x / (double)data->ray->w - 1;
		data->ray->raydir_x = data->ray->dir_x + data->ray->plane_x * data->ray->camera_x;
		data->ray->raydir_y = data->ray->dir_y + data->ray->plane_y * data->ray->camera_x;

		data->ray->map_x = (int)data->ray->pos_x;
		data->ray->map_y = (int)data->ray->pos_y;
		data->ray->delta_dist_x = (data->ray->raydir_y == 0) ? 0 : ((data->ray->raydir_x == 0) ? 1 : fabs(1 / data->ray->raydir_x));
		data->ray->delta_dist_y = (data->ray->raydir_x == 0) ? 0 : ((data->ray->raydir_y == 0) ? 1 : fabs(1 / data->ray->raydir_y));
		data->ray->hit = 0;

		//init side distance
		if (data->ray->raydir_x < 0)
		{
			data->ray->step_x = -1;
			data->ray->side_dist_x = (data->ray->pos_x - data->ray->map_x) * data->ray->delta_dist_x;
		}
		else
		{
			data->ray->step_x = 1;
			data->ray->side_dist_x = (data->ray->map_x + 1.0 - data->ray->pos_x) * data->ray->delta_dist_x;
		}
		if (data->ray->raydir_y < 0)
		{
			data->ray->step_y = -1;
			data->ray->side_dist_y = (data->ray->pos_y - data->ray->map_y) * data->ray->delta_dist_y;
		}
		else
		{
			data->ray->step_y = 1;
			data->ray->side_dist_y = (data->ray->map_y + 1.0 - data->ray->pos_y) * data->ray->delta_dist_y;
		}
		//dda
		while (data->ray->hit == 0)
		{
			if (data->ray->side_dist_x < data->ray->side_dist_y)
			{
				data->ray->side_dist_x += data->ray->delta_dist_x;
				data->ray->map_x += data->ray->step_x;
				data->ray->side = 0;
			}
			else
			{
				data->ray->side_dist_y += data->ray->delta_dist_y;
				data->ray->map_y += data->ray->step_y;
				data->ray->side = 1;
			}
			if (data->map->map[data->ray->map_y][data->ray->map_x] > 0)
				data->ray->hit = 1;
		}
		//fisheye correction
		if (data->ray->side == 0)
			data->ray->perp_wall_dist = (data->ray->map_x - data->ray->pos_x + (1 - data->ray->step_x) / 2) / data->ray->raydir_x;
		else
			data->ray->perp_wall_dist = (data->ray->map_y - data->ray->pos_y + (1 - data->ray->step_y) / 2) / data->ray->raydir_y;

		//calcul ligne start et end
		data->ray->line_height = (int)(data->ray->h / data->ray->perp_wall_dist);
		data->ray->draw_start = (data->ray->line_height * -1) / 2 + data->ray->h / 2;
		if (data->ray->draw_start < 0)
			data->ray->draw_start = 0;
		data->ray->draw_end = data->ray->line_height / 2 + data->ray->h / 2;
		if (data->ray->draw_end >= data->ray->h)
			data->ray->draw_end = data->ray->h - 1;

		data->ray->color = 0x00747474;
		if (data->ray->side == 1)
			data->ray->color = 0x00545454;

		while (data->ray->draw_start < data->ray->draw_end)
		{
			ft_mlx_pixel_put(data->img, data->ray->x, data->ray->draw_start, data->ray->color);
			data->ray->draw_start++;
		}
		if (data->ray->draw_end < 0)
			data->ray->draw_end = data->ray->h;
		int y = data->ray->draw_end;
		while (y < data->ray->h)
		{

			ft_mlx_pixel_put(data->img, data->ray->x, y, 0x0021825C);// trace le pixel du sol
			ft_mlx_pixel_put(data->img, data->ray->x, data->ray->h - y - 1, 0x00a6daef);// trace le pixel du plafond
			y++;
		}
		data->ray->x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img->img, 0, 0);
		mlx_hook(data->window, 17, 0, close_cub, data);
		mlx_hook(data->window, 2, 1L<<0, handle_keypress, data);
		mlx_hook(data->window, 3, 1L<<1, handle_keyrelease, data);
	return(1);
}

int		main(int ac, char **av)
{
	int fd;
	t_map map;
	t_key key;
	t_img img;
	t_ray ray;
	t_player player;
	t_mlx data;


	data.map = &map;
	data.key = &key;
	data.img = &img;
	data.ray = &ray;
	data.player = &player;
	data.key->key_up = 0;
	data.key->key_down = 0;
	data.key->key_left = 0;
	data.key->key_right = 0;
	data.key->key_turnleft = 0;
	data.key->key_turnright = 0;
	data.key->key_esc = 0;
	//checker le nb d'arguments
	if (ac < 2 || ac > 4)
	{
		ft_putstr("Error\nWrong number of arguments");
		exit(0);
	}
	if (ac == 3)
	{
		if (ft_strncmp("-save", av[1], ft_strlen("-save")) != 0)
		{
			ft_putstr("Error\nWrong arguments order");
			exit(0);
		}
	}
	fd = (ac == 2) ?  open(av[1], O_RDONLY) : open(av[2], O_RDONLY);
	parse_map(&data, fd);
	close(fd);

	//afficher la premiere image
	if (!(data.mlx = mlx_init()))
	{
		ft_putstr("Error\nCouldn't init MLX pointer.");
		return(EXIT_FAILURE);
	}
	data.window = mlx_new_window(data.mlx, map.res_x, map.res_y, "Cub3d");
	//prendre un screen si besoin
	//hook des touches
	data.img->img = mlx_new_image(data.mlx, map.res_x, map.res_y);
	get_img_adrr(&data);

	data.ray->pos_x = data.player->player_x;
	data.ray->pos_y = data.player->player_y + 0.5;
	data.ray->dir_x = data.player->player_dir_x;
	data.ray->dir_y = data.player->player_dir_y;
	data.ray->w = data.map->res_x;
	data.ray->h = data.map->res_y;
	data.ray->movespeed = 0.02;
	while (1)
	{
		raycasting(&data);
		//loop
		mlx_loop(data.mlx);
	}
	return (EXIT_SUCCESS);
}
