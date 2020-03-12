/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 10:51:51 by kparis            #+#    #+#             */
/*   Updated: 2020/03/12 18:30:31 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_res(char **line_args, t_mlx *data, int *parsed)
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
	*parsed += 1;
}

void	get_path(char **line_args, char *str, char **path, int *parsed)
{
	if (ft_strncmp(line_args[0], str, ft_strlen(line_args[0])) == 0)
	{
		if (ft_str_tab_len(line_args) != 2)
			error_message("Wrong number of arguments in texture path field");
		*path = ft_strdup(line_args[1]);
		*parsed += 1;
	}
}

void	parse_color(char **line_args, int *var, int *parsed)
{
	char	**colors;
	int		i;
	int		j;

	j = 0;
	if (ft_str_tab_len(line_args) != 2)
		error_message("Wrong number of arguments in floor color field");
	colors = ft_split(line_args[1], ',');
	if (ft_str_tab_len(colors) != 3)
		error_message("Wrong floor or ceilling color values");
	while (j < 3)
	{
		i = 0;
		while (colors[j][i])
		{
			if (!ft_isdigit(colors[j][i]))
				error_message("Colors can only be in rgb, please check your values");
			i++;
		}
		j += 1;
	}
	*var = get_rgb(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	ft_free_str_tab(colors, ft_str_tab_len(colors));
	*parsed += 1;
}

void	parsing_path(char **line_args, t_mlx *data, int *parsed)
{
	get_path(line_args, "NO", &data->map->n_path, parsed);
	get_path(line_args, "SO", &data->map->s_path, parsed);
	get_path(line_args, "WE", &data->map->w_path, parsed);
	get_path(line_args, "EA", &data->map->e_path, parsed);
	get_path(line_args, "S", &data->map->sprite_path, parsed);
}

void	parse_cub_args(t_mlx *data)
{
	int		fd;
	char	*line;
	char	**line_args;
	int		parsed;

	parsed = 0;
	line_args = 0;
	if ((fd = open(data->map->cub_path, O_RDONLY)) == -1)
		error_message("Cannot open this .cub file");
	while (get_next_line(fd, &line) && parsed < 8)
	{
		line_args = ft_split(line, ' ');
		if (ft_strncmp(line_args[0], "R", ft_strlen(line_args[0])) == 0)
			get_res(line_args, data, &parsed);
		parsing_path(line_args, data, &parsed);
		if (ft_strncmp(line_args[0], "F", ft_strlen(line_args[0])) == 0)
			parse_color(line_args, &data->map->floor, &parsed);
		if (ft_strncmp(line_args[0], "C", ft_strlen(line_args[0])) == 0)
			parse_color(line_args, &data->map->ceilling, &parsed);
		ft_free_str_tab(line_args, ft_str_tab_len(line_args));
		free(line);
	}
	//parse_map(fd, data);
	free(line);
	close(fd);
}
