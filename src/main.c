/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:31:57 by kparis            #+#    #+#             */
/*   Updated: 2020/02/06 16:30:01 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include <fcntl.h>

int		main(int ac, char **av)
{
	char *line;
	int fd;
	t_map map;
	t_mlx data;

	line = 0;
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
	//parser et vérifier la maps
	fd = (ac == 2) ?  open(av[1], O_RDONLY) : open(av[2], O_RDONLY);
	while(get_next_line(fd, &line))
		parser_cub(line, &map);
	close(fd);
	ft_putendl(map.sprite);
	//afficher la premiere image
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, map.res_x, map.res_y, "Cub3d");
	mlx_string_put(data.mlx, data.window, (map.res_x/2), (map.res_y/2), 0x00FFFFFF, ft_itoa(map.res_x));
	//prendre un screen si besoin
	//hook des touches
	//loop
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}