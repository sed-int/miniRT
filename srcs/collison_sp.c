/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collison_sp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:15:07 by phan              #+#    #+#             */
/*   Updated: 2023/09/19 15:15:24 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	check_ray_collison_sphere(t_ray ray, t_object obj)
{
	t_hit	hit;
	t_vec3	tmp;
	double	b;
	double	c;
	double	nabla;

	hit.d = -1.0;
	tmp = sub_vec3(ray.start, obj.sphere.center);
	b = dot_vec3(ray.dir, tmp);
	c = dot_vec3(tmp, tmp) - obj.sphere.radius * obj.sphere.radius;
	nabla = b * b - c;
	if (nabla >= 0.0)
	{
		double d1 = -b + sqrtf(nabla);
		double d2 = -b - sqrtf(nabla);
		hit.d = ((d1 < d2 ) * d1) + ((d1 >= d2) * d2);
		hit.point = add_vec3(ray.start, scale_vec3(ray.dir, hit.d));
		hit.normal = unit_vec3(sub_vec3(hit.point, obj.sphere.center));
	}
	return (hit);
}
