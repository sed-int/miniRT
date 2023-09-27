/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:03:02 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/27 14:50:07 by hcho2            ###   ########.fr       */
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
	if (type == AMBIENT)
		set_ambient(args, &rt->amb);
	else if (type == CAMERA)
		set_camera(args, &rt->cam);
	else if (type == LIGHT)
		set_light(args, &rt->light);
	else
		set_object(type, args, obj, rt);
}
