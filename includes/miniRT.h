/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:57:07 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/30 14:27:52 by hcho2            ###   ########.fr       */
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


// typedef t_vec3	t_light;

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
	t_vec3	axis[3];
	int		view_angle;
	double	fov;
}	t_cam;

typedef struct s_light
{
	t_vec3	point;
	double	ratio;
	t_vec3	color;
}	t_light;

typedef struct s_rt
{
	t_amb		amb;
	t_cam		cam;
	t_light		light;
	t_object	*objs;
}	t_rt;

int			trace_ray(t_ray ray, t_object *objects, t_vec3 light_pos);

/* parser */
void		parse_input(char *filename, void *env);
void		set_value(int type, char **args, t_rt *rt);
t_object	*new_obj(void);
void		obj_lstadd_back(t_object **lst, t_object *new);

/* setter */
void		set_dir(char *arg, t_vec3 *dir);
void		set_ratio(char *arg, double	*ratio);
void		set_color(char *arg, t_vec3 *color);
void		set_point(char *arg, t_vec3 *point);
void		set_value(int type, char **args, t_rt *rt);

void		set_object(int type, char **args, t_rt *rt);
void		set_camera(char **args, t_cam *cam);
void		set_ambient(char **args, t_amb *amb);
void		set_light(char **args, t_light *light);
void		set_sphere(char **args, t_object *obj, t_rt *rt);
void		set_plane(char **args, t_object *obj, t_rt *rt);
void		set_cylinder(char **args, t_object *obj, t_rt *rt);

/* view transform */
void		view_transform(t_object *obj, t_cam cam);

#endif
