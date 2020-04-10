/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:11:27 by kparis            #+#    #+#             */
/*   Updated: 2020/04/10 04:45:32 by kparis           ###   ########.fr       */
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
	int		map_len;
	char	dir;
	char	**map;
}				t_map;

typedef struct	s_img
{
	void		*img_ptr;
	void		*adress;
	int			bits_per_pxl;
	int			line_length;
	int			endian;
	int			*colors;
	int			x;
	int			y;
}				t_img;

typedef struct	s_ray
{
	int			init;
	double		dir_x;
	double		dir_y;
	double		pos_x;
	double		pos_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		move_speed;
	double		rot_speed;
}				t_ray;

typedef struct	s_mlx
{
	int		k_up;
	int		k_down;
	int		k_left;
	int		k_right;
	int		k_esc;
	int		k_turn_left;
	int		k_turn_right;
	t_map	*map;
	void	*mlx;
	void	*window;
	t_img	*img;
	t_ray	*ray;

}				t_mlx;

void			parse_cub_args(t_mlx *data);
void			error_message(char *text);
int				get_rgb(int r, int g, int b);
void			get_img_adrr(t_mlx *data);
void			create_texture_img(t_mlx *data, char *path, t_img *text);
void			clear(t_mlx *data);
void			ft_mlx_pixel_put(t_img *img, int x, int y, int color);
int				close_mlx(t_mlx *data);
void			parse_map(int fd, t_mlx *data);
int				keypress(int keycode, t_mlx *data);
int				keyrelease(int keycode, t_mlx *data);
void			raycasting(t_mlx *data, t_ray *ray);
void			init_ray(t_mlx *data, t_ray *ray);
void			dda(t_mlx *data, t_ray *ray);
void			move(t_mlx *data, t_ray *ray);
int				loop(t_mlx *data);
#endif
