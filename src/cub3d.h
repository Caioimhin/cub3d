/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:11:27 by kparis            #+#    #+#             */
/*   Updated: 2020/03/27 17:39:51 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../miniLibX/mlx.h"

# define RES_X_MAX 2560
# define RES_Y_MAX 1440
# define RES_X_MIN 192
# define RES_Y_MIN 108
# define ESC 53
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define TURN_LEFT 123
# define TURN_RIGHT 124

typedef struct	s_map
{
	int		save;
	char	*cub_path;
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
	char	*sprite_path;
	int		res_x;
	int		res_y;
	int		floor;
	int		ceilling;
	int		pos_x;
	int		pos_y;
	char	**map;
}				t_map;

typedef struct	s_img
{
	void		*img_ptr;
	void		*img_cpy;
	void		*adress;
	int			bits_per_pxl;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	t_map	*map;
	void	*mlx;
	void	*window;
	t_img	*img;

}				t_mlx;

void			parse_cub_args(t_mlx *data);
void			error_message(char *text);
int				get_rgb(int r, int g, int b);
void			get_img_adrr(t_mlx *data);
void			ft_mlx_pixel_put(t_img *img, int x, int y, int color);
int				close_mlx(t_mlx *data);
void			parse_map(int fd, t_mlx *data);
int				raycasting(t_mlx *data);
#endif
