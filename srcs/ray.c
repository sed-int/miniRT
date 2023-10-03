/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:03:37 by phan              #+#    #+#             */
/*   Updated: 2023/10/02 14:27:55 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"

static t_hit   find_closest_collisun(t_ray ray, t_object *objects)
{
	double	closest_d = 10000.0;
	t_hit	closest_hit;
	t_hit	hit;

	closest_hit.d = -1.0;
	while (objects)
	{
		hit = objects->check_ray_collison(ray, *objects);
		if (hit.d >= 0.0 && hit.d < closest_d)
		{
			closest_d = hit.d;
			closest_hit = hit;
			closest_hit.obj = objects;
		}
		objects = objects->next;
	}
	return (closest_hit);
}

static unsigned int	get_rgb(int r, int g, int b)
{
	if (r > 0xFF)
		r = 0xFF;
	if (g > 0xFF)
		g = 0xFF;
	if (b > 0xFF)
		b = 0xFF;
	return (0x00 << 24 | r << 16 | g << 8 | b);
}

int	trace_ray(t_ray ray, t_object *objects, t_light light, t_amb amb)
{
	t_hit		hit;
	t_object	obj;

	hit = find_closest_collisun(ray, objects);
	if (hit.d < 0)
		return (get_rgb(amb.color.r * amb.ratio, amb.color.g * amb.ratio, amb.color.b * amb.ratio));
	t_vec3	dir2light = unit_vec3(sub_vec3(light.point, hit.point));
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
