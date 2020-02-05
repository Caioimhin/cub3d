/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:31:57 by kparis            #+#    #+#             */
/*   Updated: 2020/02/05 17:12:11 by kparis           ###   ########.fr       */
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

	line = 0;
	//checker le nb d'arguments
	(void)av;
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
	{
		(line[0] == 'R') ? map.res = ft_strdup(&line[2]) : 0;
		(line[0] == 'N') ? map.north = ft_strdup(&line[3]) : 0;
		(line[0] == 'S' && line[1] == 'O') ? map.south = ft_strdup(&line[3]) : 0;
		(line[0] == 'W') ? map.west = ft_strdup(&line[3]) : 0;
		(line[0] == 'E') ? map.east = ft_strdup(&line[3]) : 0;
		(line[0] == 'S' && line[1] == ' ') ? map.sprite = ft_strdup(&line[2]) : 0;
		(line[0] == 'F') ? map.floor = ft_strdup(&line[2]) : 0;
		(line[0] == 'C') ? map.ceiling = ft_strdup(&line[2]) : 0;
	}
	ft_putendl(map.east);
	//afficher la premiere image
	//prendre un screen si besoin
	//hook des touches
	//loop
	return (1);
}