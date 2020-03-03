/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:31:57 by kparis            #+#    #+#             */
/*   Updated: 2020/03/03 17:59:17 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include <fcntl.h>

int		main(int ac, char **av)
{
	int fd;
	t_map		map;
	t_key		key;
	t_img		img;
	t_player	player;
	t_ray		ray;
	t_mlx		data;


	data.map = &map;
	data.key = &key;
	data.img = &img;
	data.player = &player;
	data.ray = &ray;
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

	//=====================RAY CASTING =================================
	ray.pos_x = player.player_x;
	ray.pos_y = player.player_y;
	ray.dir_x = player.player_dir_x;
	ray.dir_y = player.player_dir_y;
	ray.plane_x = 0;
	ray.plane_y = 0.66;
	ray.w = map.width_map;
	ray.h = map.height_map;
	while (1)
	{
		ft_putendl("entre dans la boucle 1");
		ray.x = 0;
		while (ray.x < ray.w)
		{
			ft_putendl("entre dans la boucle 2");
			//init
			ray.camera_x = 2 * ray.x / (double)ray.w - 1;
			ray.raydir_x = ray.dir_x + ray.plane_x * ray.camera_x;
			ray.raydir_y = ray.dir_y + ray.plane_y * ray.camera_x;
			//where on the grid
			ray.map_x = (int)ray.pos_x;
			ray.map_y = (int)ray.pos_y;
			ray.delta_dist_x = (ray.raydir_y == 0) ? 0 : ((ray.raydir_x == 0) ? 1 : fabs(1 / ray.raydir_x));
			ray.delta_dist_y = (ray.raydir_x == 0) ? 0 : ((ray.raydir_y == 0) ? 1 : fabs(1 / ray.raydir_y));
			ray.hit = 0;
			//calcul each step
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
			//dda (cast a ray untill a wall is found)
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
				if (map.map[ray.map_y][ray.map_x] > 0)
					ray.hit = 1;
			}
			//anti fisheye
			if (ray.side == 0)
				ray.perp_wall_dist = (ray.map_x - ray.pos_x + (1 - ray.step_x) / 2) / ray.raydir_x;
			else
				ray.perp_wall_dist = (ray.map_y - ray.pos_y + (1 - ray.step_y) / 2) / ray.raydir_y;
			ray.line_height = (int)(ray.h / ray.perp_wall_dist);
			ft_putnbr(ray.line_height);
			ft_putchar('\n');
			//init draw values
			ray.draw_start = (ray.line_height * -1) / 2 + ray.h / 2;
			ray.draw_end = ray.line_height / 2 + ray.h / 2;
			if (ray.draw_start < 0)
				ray.draw_start = 0;
			if (ray.draw_end >= ray.h)
				ray.draw_end = ray.h - 1;
			//draw
			if (ray.side == 0)
				ray.color = 0x003160ad;
			else
				ray.color = 0X002c4d85;

			while (ray.draw_start < ray.draw_end)
			{
				ft_putnbr(ray.x);
				ft_putchar(';');
				ft_putnbr(ray.draw_start);
				ft_putchar('\n');
				ft_mlx_pixel_put(&img, ray.x, ray.draw_start, ray.color);
				ray.draw_start++;
			}
			ray.x++;
		}
		mlx_put_image_to_window(data.mlx, data.window, img.img, 0, 0);
		mlx_hook(data.window, 17, 0, close_cub, &data);
		mlx_hook(data.window, 2, 1L<<0, handle_keypress, &data);
		mlx_hook(data.window, 3, 1L<<1, handle_keyrelease, &data);
		//loop
		mlx_loop(data.mlx);
	}
	//==================================================================
	return (EXIT_SUCCESS);
}
