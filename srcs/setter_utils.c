/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:27:23 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/30 16:06:34 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_camera(char **args, t_cam *cam)
{
	t_vec3	vup;

	set_point(args[1], &cam->point);
	set_dir(args[2], &cam->dir);
	cam->view_angle = ft_atoi(args[3]) / 2.0;
	// cam->point = add_vec3(cam->point,\
	// 	scale_vec3(cam->dir, WIDTH / 2.0));
	cam->fov = tan(cam->view_angle * (M_PI / 180));
	vup = set_vec3(0, 1, 0);
	// if (cam->dir.y != 0.0)
	// 	vup = set_vec3(0, 0, 1);
	cam->axis[2] = unit_vec3(cam->dir);
	cam->axis[0] = unit_vec3(cross_vec3(vup, cam->axis[2]));
	cam->axis[1] = unit_vec3(cross_vec3(cam->axis[2], cam->axis[0]));
	// cam->axis[1] = cross_vec3(cam->axis[0], cam->dir);
	// printf("axis 1 : ");
	// print_vec3(cam->axis[0]);
	// print_vec3(cam->axis[1]);
}

void	set_ambient(char **args, t_amb *amb)
{
	set_ratio(args[1], &amb->ratio);
	set_color(args[2], &amb->color);
}

void	set_light(char **args, t_light *light)
{
	set_point(args[1], &light->point);
	set_ratio(args[2], &light->ratio);
	set_color(args[3], &light->color);
}
