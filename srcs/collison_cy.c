/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collison_cy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:15:03 by phan              #+#    #+#             */
/*   Updated: 2023/09/19 16:28:47 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_over_cylinder_range(double h, double max)
{
	if (h < 0.0 || h > max)
		return (1);
	return (0);
}

int check_ray_cylinder_side(t_ray ray, t_cylinder cylinder, t_vec3 *point, t_vec3 *normal, double *d)
{
	double	a;
	double	b;
	double	c;
	double	nabla;
	t_vec3	vsub;

	vsub = sub_vec3(ray.start, cylinder.center);
	a = pow(dot_vec3(ray.dir, cylinder.normal), 2.0) - 1.0;
	b = dot_vec3(ray.dir, cylinder.normal) * dot_vec3(vsub, cylinder.normal) - dot_vec3(vsub, ray.dir);
	c = pow(cylinder.diameter / 2.0, 2.0f) - dot_vec3(vsub, vsub) + pow(dot_vec3(vsub, cylinder.normal), 2.0);
	nabla = b * b - a * c;
	if (nabla >= 0.0)
	{
		double d1 = (-b + sqrt(nabla)) / a;
		double d2 = (-b - sqrt(nabla)) / a;
		if (d1 < 0.0)
			*d = d2;
		else if (d2 < 0.0)
			*d = d1;
		else
			*d = ((d1 < d2) * d1) + ((d1 >= d2) * d2);
		*point = add_vec3(ray.start, scale_vec3(ray.dir, *d));
		if (is_over_cylinder_range(dot_vec3(sub_vec3(*point, cylinder.center), cylinder.normal), cylinder.height))
			return (0);
		*normal = unit_vec3(sub_vec3(sub_vec3(*point, cylinder.center), \
			scale_vec3(cylinder.normal, \
			dot_vec3(sub_vec3(*point, cylinder.center), cylinder.normal))));
		return (1);
	}
	return (0);
}

int check_ray_cylinder_base_plane(t_ray ray, t_cylinder cylinder, t_vec3 *point, t_vec3 *normal, double *d)
{
	t_vec3	in_base_plnae;
	double	d1;
	double	d2;

	if (fabs(dot_vec3(cylinder.normal, ray.dir)) < 1e-2)
		return (0);
	d1 = (dot_vec3(add_vec3(scale_vec3(cylinder.normal, cylinder.height), cylinder.center), cylinder.normal) - dot_vec3(cylinder.normal, ray.start)) / dot_vec3(ray.dir, cylinder.normal);
	d2 = (dot_vec3(cylinder.center, cylinder.normal) - dot_vec3(cylinder.normal, ray.start)) / dot_vec3(ray.dir, cylinder.normal);
	*d = ((d1 < d2 ) * d1) + ((d1 >= d2) * d2);
	if (*d < 0.0)
		return (0);
	*point = add_vec3(ray.start, scale_vec3(ray.dir, *d));
	in_base_plnae = sub_vec3(sub_vec3(*point, cylinder.center), scale_vec3(cylinder.normal, \
		dot_vec3(sub_vec3(*point, cylinder.center), cylinder.normal)));
	if (dot_vec3(in_base_plnae, in_base_plnae) > pow(cylinder.diameter / 2, 2.0))
		return (0);
	if (*d == d1)
		*normal = cylinder.normal;
	else
		*normal = scale_vec3(cylinder.normal, -1.0);
	return (1);
}

t_hit	check_ray_collison_cylinder(t_ray ray, t_object obj)
{
	t_hit	hit;
	t_vec3	point;
	t_vec3	normal;
	double	d;

	hit.d = -1.0;
	if (check_ray_cylinder_base_plane(ray, obj.cylinder, &point, &normal, &d) ||
		check_ray_cylinder_side(ray, obj.cylinder, &point, &normal, &d))
	{
		hit.d = d;
		hit.point = point;
		hit.normal = normal;
	}
	return (hit);
}
