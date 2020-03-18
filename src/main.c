/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 10:30:10 by kparis            #+#    #+#             */
/*   Updated: 2020/03/18 23:39:21 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_message(char *text)
{
	ft_putendl("Error");
	ft_putstr(text);
	exit(0);
}

int		check_args(int ac, char **av, t_mlx *data)
{
	if (ac < 2 || ac > 3)
		error_message("Invalid arguments number");
	else
	{
		if (ac == 3 && ft_strncmp(av[1], "--save", 6) == 0)
		{
			data->map->cub_path = av[2];
			return (1);
		}
		else if (ac == 3 && ft_strncmp(av[1], "--save", 6) != 0)
			error_message("Invalid argument");
	}
	data->map->cub_path = av[1];
	return (0);
}

int		main(int ac, char **av)
{
	t_map	map;
	t_mlx	data;

	data.map = &map;
	data.map->save = check_args(ac, av, &data);
	parse_cub_args(&data);
	data.map->map = 0;
	data.map->map = ft_realloc_char_tab(data.map->map, "test");
	return (0);
}
