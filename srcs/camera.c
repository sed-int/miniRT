/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 13:49:51 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/30 17:21:30 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	get_obj_position(t_object *obj)
{
	if (obj->type == SPHERE)
		return (obj->sphere.center);
	if (obj->type == PLANE)
		return (obj->plane.point);
	if (obj->type == CYLINDER)
		return (obj->cylinder.center);
	return (set_vec3(0, 0, 0));
}

void	set_obj_position(t_object *obj, t_vec3 new)
{
	if (obj->type == SPHERE)
		obj->sphere.center = new;
	else if (obj->type == PLANE)
		obj->plane.point = new;
	else if (obj->type == CYLINDER)
		obj->cylinder.center = new;
}

void	view_transform(t_object *obj, t_cam cam)
{
	t_vec3	pos;
	t_vec3	new;

	while (obj)
	{
		pos = get_obj_position(obj);
		printf("u : ");
		print_vec3(cam.axis[0]);
		printf("v : ");
		print_vec3(cam.axis[1]);
		printf("n : ");
		print_vec3(cam.axis[2]);
		printf("cam : ");
		print_vec3(cam.point);
		new.x = cam.axis[0].x * pos.x + cam.axis[0].y * pos.y + cam.axis[0].z * pos.z - cam.point.x;
		new.y = cam.axis[1].x * pos.x + cam.axis[1].y * pos.y + cam.axis[1].z * pos.z - cam.point.y;
		new.z = cam.axis[2].x * pos.x + cam.axis[2].y * pos.y + cam.axis[2].z * pos.z - cam.point.z;
		// new.x = cam.axis[0].x * pos.x + cam.axis[0].y * pos.y + cam.axis[0].z * pos.z;
		// new.y = cam.axis[1].x * pos.x + cam.axis[1].y * pos.y + cam.axis[1].z * pos.z;
		// new.z = cam.axis[2].x * pos.x + cam.axis[2].y * pos.y + cam.axis[2].z * pos.z;
		set_obj_position(obj, new);
		printf("new pos: ");
		print_vec3(get_obj_position(obj));
		obj = obj->next;
	}
}
