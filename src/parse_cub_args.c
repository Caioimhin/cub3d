/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 10:51:51 by kparis            #+#    #+#             */
/*   Updated: 2020/03/11 18:08:46 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_res(char **line_args, t_mlx *data)
{
	int i;

	i = 0;
	if (ft_str_tab_len(line_args) != 3)
		error_message("wrong argument number in resolution field");
	while (line_args[1][i])
	{
		if (!ft_isdigit(line_args[1][i]))
			error_message("Wrong X resolution");
			i++;
	}
	i = 0;
	while (line_args[2][i])
	{
		if (!ft_isdigit(line_args[2][i]))
			error_message("Wrong Y resolution");
			i++;
	}
	data->map->res_x = ft_atoi(line_args[1]);
	data->map->res_y = ft_atoi(line_args[2]);
}

void	get_path(char **line_args, t_mlx *data)
{
	if (ft_str_tab_len(line_args) != 2)
		error_message("wrong argument number in resolution field");
	if (ft_strncmp(line_args[0], "NO", ft_strlen(line_args[0])) == 0)
		data->map->n_path = ft_strdup(line_args[1]);
	else if (ft_strncmp(line_args[0], "SO", ft_strlen(line_args[0])) == 0)
		data->map->n_path = ft_strdup(line_args[1]);
	else if (ft_strncmp(line_args[0], "WE", ft_strlen(line_args[0])) == 0)
		data->map->n_path = ft_strdup(line_args[1]);
	else if (ft_strncmp(line_args[0], "EA", ft_strlen(line_args[0])) == 0)
		data->map->n_path = ft_strdup(line_args[1]);
	else if (ft_strncmp(line_args[0], "S", ft_strlen(line_args[0])) == 0)
		data->map->n_path = ft_strdup(line_args[1]);
}

void	parse_cub_args(t_mlx *data)
{
	int fd;
	char *line;
	char **line_args;
	int parsed;

	parsed = 0;
	line_args = 0;
	if ((fd = open(data->map->cub_path, O_RDONLY)) == -1)
		error_message("Cannot open this file");
	while(get_next_line(fd, &line) && parsed < 8)
	{
		if (line_args)
			ft_free_str_tab(line_args, ft_str_tab_len(line_args));
		line_args = ft_split(line, ' ');
		//si
			//resolution
		if (ft_strncmp(line_args[0], "R", ft_strlen(line_args[0])) == 0)
			get_res(line_args, data);
			//textures
			get_path(line_args, data);
			//sol
			//plafond
		free(line);
		parsed += 1;
	}
	close(fd);
	ft_putendl(data->map->n_path);
}
