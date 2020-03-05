/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:31:57 by kparis            #+#    #+#             */
/*   Updated: 2020/03/05 18:01:34 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include <fcntl.h>

void init(t_mlx *data)
{
	data->key->key_up = 0;
	data->key->key_down = 0;
	data->key->key_left = 0;
	data->key->key_right = 0;
	data->key->key_turnleft = 0;
	data->key->key_turnright = 0;
	data->key->key_esc = 0;

	data->ray->pos_x = data->player->player_x;
	data->ray->pos_y = data->player->player_y + 0.5;
	data->ray->dir_x = data->player->player_dir_x;
	data->ray->dir_y = data->player->player_dir_y;
	data->ray->w = data->map->res_x;
	data->ray->h = data->map->res_y;
	data->ray->plane_x = 0;
	data->ray->plane_y = 0.66;
	data->ray->movespeed = 0.2;
}

int		retrieve_args(int ac, char **av, t_mlx *data)
{
	int fd;

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
	parse_map(data, fd);
	close(fd);

	//afficher la premiere image
	if (!(data->mlx = mlx_init()))
	{
		ft_putstr("Error\nCouldn't init MLX pointer.");
		return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	t_mlx data;
	t_map map;
	t_key key;
	t_img img;
	t_ray ray;
	t_player player;


	data.map = &map;
	data.key = &key;
	data.img = &img;
	data.ray = &ray;
	data.player = &player;
	if (retrieve_args(ac, av, &data) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	init(&data);
	data.window = mlx_new_window(data.mlx, map.res_x, map.res_y, "Cub3d");
	//hook des touches
	data.img->img = mlx_new_image(data.mlx, map.res_x, map.res_y);
	get_img_adrr(&data);
	//==================================RAY CASTING=============================


	raycasting(data.ray, &data);
	mlx_hook(data.window, 17, 0, close_cub, &data);
	mlx_hook(data.window, 2, 1L<<0, handle_keypress, &data);
	mlx_hook(data.window, 3, 1L<<1, handle_keyrelease, &data);

	mlx_loop_hook(data.mlx, &loop, &data);
	//==================================RAY CASTING=============================
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
