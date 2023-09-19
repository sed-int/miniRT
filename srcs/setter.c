/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:03:02 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/17 17:21:21 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_dir(char *arg, t_vec3 *dir)
{
	char	**splitted;

	splitted = ft_split(arg, ',');
	if (split_len(splitted) != 3)
		exit(1);
	dir->x = atof(arg[0]);
	dir->y = atof(arg[1]);
	dir->z = atof(arg[2]);
	if (x > 1 || x < -1 || x > 1 || x < -1 || z > 1 || z < -1)
		exit(1);
}

void	set_ratio(char *arg, double	*ratio)
{
	ratio = atof(arg);
	if (ratio < 0 || ratio > 1)
		exit(1);
}

void	set_color(char *arg, t_vec3 *color)
{
	char	**splitted;

	splitted = ft_split(arg, ',');
	if (split_len(splitted) != 3)
		exit(1);
	color->r = atof(arg[0]);
	color->g = atof(arg[1]);
	color->b = atof(arg[2]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		exit(1);
}

void	set_point(char *arg, t_vec3 *point)
{
	char	**splitted;

	splitted = ft_split(arg, ',');
	if (split_len(splitted) != 3)
		exit(1);
	point->x = atof(arg[0]);
	point->y = atof(arg[1]);
	point->z = atof(arg[2]);
}

void	set_value(int type, char **args, t_rt *rt)
{
	if (type == AMBIENT)
	{
		set_ratio(args[0], &rt->amb.ratio);
		set_color(args[1], &rt->amb.color);
	}
	else if (type == CAMERA)
	{
		set_point(args[0], &rt->cam.point);
		set_dir(args[1], &rt->cam.dir);
	}
	else if (type == LIGHT)
	{
		set_point(args[0], &rt->light.point);
		set_ratio(args[1], &rt->light.ratio);
		set_color(args[2], &rt->light.color);
	}
	else if (type == SPHERE)
	{
		set_point(args[0], &rt->objs[SPHERE].sphere.center);
		rt->objs[SPHERE].sphere.radius = ft_atof(args[1]) / 2;
		set_color(args[1], &rt->objs[SPHERE].diffuse);
	}
	else if (type == PLANE)
	{
		set_point(args[0], &rt->objs[PLANE].plane.point);
		set_dir(args[1], &rt->objs[PLANE].plane.normal);
		set_color(args[2], &rt->objs[PLANE].diffuse);
	}
	else if (type == CYLINDER)
	{
		set_point(args[0], &rt->objs[CYLINDER].cylinder.center);
		set_dir(args[1], &rt->objs[CYLINDER].cylinder.normal);
		rt->objs[CYLINDER].cylinder.diameter = ft_atof(args[2]);
		rt->objs[CYLINDER].cylinder.height = ft_atof(args[3]);
		set_color(args[4], &rt->objs[CYLINDER].diffuse);
	}
}
