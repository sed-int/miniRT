/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:03:37 by phan              #+#    #+#             */
/*   Updated: 2023/09/19 16:04:52 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"

static t_hit   find_closest_collisun(t_ray ray, t_object *objects)
{
	double	closest_d = 10000.0;
	t_hit	closest_hit;
	t_hit	hit;

	closest_hit.d = -1.0;
	for (int i = 0; i < 1; i++) {
		hit = objects[i].check_ray_collison(ray, objects[i]);
		if (hit.d >= 0.0 && hit.d < closest_d)
		{
			closest_d = hit.d;
			closest_hit = hit;
			closest_hit.obj = &objects[i];
		}
	}
	return (closest_hit);
}

int	trace_ray(t_ray ray, t_object *objects, t_light light_pos)
{
	t_hit		hit;
	t_object	obj;

	hit = find_closest_collisun(ray, objects);
	if (hit.d < 0)
		return (0);
	t_vec3	dir2light = unit_vec3(sub_vec3(light_pos, hit.point));
	double	diff = dot_vec3(dir2light, hit.normal);
	obj = *(hit.obj);
	diff = (diff >= 0.0) * diff;
	obj.diffuse = scale_vec3(obj.diffuse, diff);
	t_vec3	reflected_dir = \
		sub_vec3(\
		scale_vec3(hit.normal, dot_vec3(hit.normal, dir2light) * 2.0), \
		dir2light);
	double	spec = dot_vec3(scale_vec3(ray.dir, -1.0), reflected_dir);
	spec = (spec >= 0.0) * spec;
	spec = powf(spec, 9.0);
	obj.specular = scale_vec3(obj.specular, spec * 0.8);
	obj.color = add_vec3(add_vec3(obj.amb, obj.diffuse), obj.specular);
	return (get_rgb(obj.color.r, obj.color.g, obj.color.b));
}