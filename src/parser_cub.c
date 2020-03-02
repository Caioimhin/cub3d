/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:22:44 by kparis            #+#    #+#             */
/*   Updated: 2020/02/19 12:40:14 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "cub3d.h"

int		get_rgb(int r, int g, int b)
{
	int	rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

 static void	parse_color(char *line, t_map *map)
 {
	int i;
	int r;
	int g;
	int b;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	r = ft_atoi(&line[i]);
	while (line[i] != ',')
		i++;
	i++;
	g = ft_atoi(&line[i]);
	while (line[i] != ',')
		i++;
	i++;
	b = ft_atoi(&line[i]);
	if (line[0] == 'F')
		map->floor = get_rgb(r, g, b);
	else if (line[0] == 'C')
		map->ceiling = get_rgb(r, g, b);
	//free(line);
 }

 static void	parse_path(char *line, t_map *map)
 {
	(ft_strnstr(line, "NO", 2)) ? map->north = &line[3] : 0;
	(ft_strnstr(line, "SO", 2)) ? map->south = &line[3] : 0;
	(ft_strnstr(line, "WE", 2)) ? map->west = &line[3] : 0;
	(ft_strnstr(line, "EA", 2)) ? map->east = &line[3] : 0;
	(line[0] == 'S') ? map->sprite = &line[2] : 0;
 }

 static void	parse_res(char *line, t_map *map)
 {
	 int i;

	 i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	map->res_x = ft_atoi(&line[i]);
	while(ft_isdigit(line[i]))
		i++;
	map->res_y = ft_atoi(&line[i]);

	if (map->res_x > RES_X_MAX)
		map->res_x = RES_X_MAX;
	if (map->res_y > RES_Y_MAX)
		map->res_y = RES_Y_MAX;
	//free(line);
 }

 void	parser_cub(char *line, t_map *map)
 {
	if (line[0] == 'R')
	{
		parse_res(line, map);
		return;
	}
	parse_path(line, map);
	if (line[0] == 'F' || line[0] == 'C')
		parse_color(line, map);
 }