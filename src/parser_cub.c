/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:22:44 by kparis            #+#    #+#             */
/*   Updated: 2020/02/06 16:27:30 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "cub3d.h"

 static void	parse_path(char *line, t_map *map)
 {
	if (ft_strnstr(line, "NO", 2))
		map->north = ft_substr(line, 3, ft_strlen(line));
	else if (ft_strnstr(line, "SO", 2))
		map->south = ft_substr(line, 3, ft_strlen(line));
	else if (ft_strnstr(line, "WE", 2))
		map->west = ft_substr(line, 3, ft_strlen(line));
	else if (ft_strnstr(line, "EA", 2))
		map->east = ft_substr(line, 3, ft_strlen(line));
	else if (line[0] == 'S')
		map->sprite = ft_substr(line, 2, ft_strlen(line));
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
 }

 void	parser_cub(char *line, t_map *map)
 {
	if (line[0] == 'R')
		parse_res(line, map);
	parse_path(line, map);
 }