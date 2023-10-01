/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 13:49:51 by hcho2             #+#    #+#             */
/*   Updated: 2023/10/01 19:17:15 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	get_obj_position(t_object *obj)
{
	// if (obj->type == SPHERE)
	// 	return (obj->sphere.center);
	// if (obj->type == PLANE)
	// 	return (obj->plane.point);
	// if (obj->type == CYLINDER)
	// 	return (obj->cylinder.center);
	// return (set_vec3(0, 0, 0));
	return (obj->orig);
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
		new = sub_vec3(pos, cam.point);
		// new.x = cam.axis[0].x * pos.x + cam.axis[0].y * pos.y + cam.axis[0].z * pos.z - cam.point.x;
		// new.y = cam.axis[1].x * pos.x + cam.axis[1].y * pos.y + cam.axis[1].z * pos.z - cam.point.y;
		// new.z = cam.axis[2].x * pos.x + cam.axis[2].y * pos.y + cam.axis[2].z * pos.z - cam.point.z;
		// new.x = dot_vec3(cam.axis[0], sub_vec3(pos, cam.point));
		// new.y = dot_vec3(cam.axis[1], sub_vec3(pos, cam.point));
		// new.z = dot_vec3(cam.axis[2], sub_vec3(pos, cam.point));
		set_obj_position(obj, new);
		printf("new pos: ");
		print_vec3(new);
		obj = obj->next;
	}
}
