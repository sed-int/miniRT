/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:03:02 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/19 17:44:23 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_dir(char *arg, t_vec3 *dir)
{
	char	**splitted;

	splitted = ft_split(arg, ',');
	// if (split_len(splitted) != 3)
	// 	exit(1);
	dir->x = atof(splitted[0]);
	dir->y = atof(splitted[1]);
	dir->z = atof(splitted[2]);
	if (dir->x > 1 || dir->x < -1 || \
		dir->y > 1 || dir->y < -1 || \
		dir->z > 1 || dir->z < -1)
		{
			printf("d\n");
			exit(1);
		}
}

void	set_ratio(char *arg, double	*ratio)
{
	*ratio = atof(arg);
	if (*ratio < 0 || *ratio > 1)
		{
			printf("ra\n");
			exit(1);
		}
}

void	set_color(char *arg, t_vec3 *color)
{
	char	**splitted;

	printf("color set :%s\n", arg);
	splitted = ft_split(arg, ',');
	// if (split_len(splitted) != 3)
	// 	exit(1);
	color->r = atof(splitted[0]);
	printf("1\n");
	color->g = atof(splitted[1]);
	printf("2\n");
	color->b = atof(splitted[2]);
	printf("3\n");
	if (color->r > 255 || color->r < 0 \
		|| color->g > 255 || color->g < 0 \
		|| color->b > 255 || color->b < 0)
		{
			printf("color\n");
			exit(1);
		}
}

void	set_point(char *arg, t_vec3 *point)
{
	char	**splitted;

	splitted = ft_split(arg, ',');
	// if (split_len(splitted) != 3)
	// 	exit(1);
	point->x = atof(splitted[0]);
	point->y = atof(splitted[1]);
	point->z = atof(splitted[2]);
}

void	set_value(int type, char **args, t_rt *rt)
{
	t_object	*new;

	if (type == AMBIENT)
	{
		set_ratio(args[1], &(rt->amb.ratio));
		set_color(args[2], &(rt->amb.color));
	}
	else if (type == CAMERA)
	{
		set_point(args[1], &rt->cam.point);
		set_dir(args[2], &rt->cam.dir);
	}
	else if (type == LIGHT)
	{
		set_point(args[1], &rt->light.point);
		set_ratio(args[2], &rt->light.ratio);
		set_color(args[3], &rt->light.color);
	}
	else if (type == SPHERE)
	{
		new = new_obj();
		set_point(args[1], &new->sphere.center);
		new->sphere.radius = atof(args[2]) / 2;
		set_color(args[3], &new->diffuse);
		new->amb = scale_vec3(new->diffuse, 0.2);
		new->specular = set_vec3(rt->light.color.r, rt->light.color.g, rt->light.color.b);
		new->check_ray_collison = check_ray_collison_sphere;
		obj_lstadd_back(&(rt->objs), new);
	}
	else if (type == PLANE)
	{
		new = new_obj();
		set_point(args[1], &new->plane.point);
		set_dir(args[2], &new->plane.normal);
		set_color(args[3], &new->diffuse);
		new->amb = scale_vec3(new->diffuse, 0.2);
		new->specular = set_vec3(rt->light.color.r, rt->light.color.g, rt->light.color.b);
		new->check_ray_collison = check_ray_collison_plane;
		obj_lstadd_back(&(rt->objs), new);
	}
	else if (type == CYLINDER)
	{
		new = new_obj();
		set_point(args[1], &new->cylinder.center);
		set_dir(args[2], &new->cylinder.normal);
		new->cylinder.diameter = atof(args[3]);
		new->cylinder.height = atof(args[4]);
		set_color(args[5], &new->diffuse);
		new->amb = scale_vec3(new->diffuse, 0.2);
		new->specular = set_vec3(rt->light.color.r, rt->light.color.g, rt->light.color.b);
		new->check_ray_collison = check_ray_collison_cylinder;
		obj_lstadd_back(&(rt->objs), new);
	}
}
