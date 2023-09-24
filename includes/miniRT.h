/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:57:07 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/24 16:23:00 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "object.h"
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define WIDTH	1280
# define HEIGHT	720

enum	e_type
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
};

typedef t_vec3	t_light;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_env;

typedef struct s_amb
{
	double	ratio;
	t_vec3	color;
}	t_amb;

typedef struct s_cam
{
	t_vec3	point;
	t_vec3	dir;
	t_vec3	horiz;
	t_vec3	vert;
	t_vec3	axis[3];
	int		view_angle;
	double	fov;
}	t_cam;

typedef struct s_lgt
{
	t_vec3	point;
	double	ratio;
	t_vec3	color;
}	t_lgt;

typedef struct s_rt
{
	t_amb		amb;
	t_cam		cam;
	t_lgt		light;
	t_object	*objs;
}	t_rt;

int	trace_ray(t_ray ray, t_object *objects, t_light light_pos);

// parse
void	parse_input(char *filename, void *env);
void	set_value(int type, char **args, t_rt *rt);
t_object	*new_obj();
void	obj_lstadd_back(t_object **lst, t_object *new);

#endif
