/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collison_cy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:15:03 by phan              #+#    #+#             */
/*   Updated: 2023/10/11 14:22:35 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_ray_cylinder_side(t_ray ray, t_cylinder cy, t_hit *hit)
{
	t_obj_exp_var	var;

	init_cy_exp_var(ray, cy, &var);
	if (var.nabla >= 0.0)
	{
		hit->d = get_side_distance(var.a, var.b, var.nabla);
		hit->point = add_vec3(ray.start, scale_vec3(ray.dir, hit->d));
		var.vsub = sub_vec3(hit->point, cy.center);
		var.vdot = dot_vec3(var.vsub, cy.normal);
		if (is_over_cylinder_range(var.vdot, cy.height))
			return (0);
		hit->normal = \
			unit_vec3(\
				sub_vec3(var.vsub, scale_vec3(cy.normal, var.vdot)) \
			);
		return (1);
	}
	return (0);
}

int	check_ray_cylinder_base_plane(t_ray ray, t_cylinder cy, t_hit *hit)
{
	t_vec3	in_base_plnae;
	double	d1;
	double	d2;

	if (fabs(dot_vec3(cy.normal, ray.dir)) < 1e-2)
		return (0);
	hit->d = get_base_distance(ray, cy, &d1, &d2);
	if (hit->d < 0.0)
		return (0);
	hit->point = add_vec3(ray.start, scale_vec3(ray.dir, hit->d));
	in_base_plnae = sub_vec3(\
		sub_vec3(hit->point, cy.center), \
		scale_vec3(\
		cy.normal, \
		dot_vec3(sub_vec3(hit->point, cy.center), cy.normal) \
	));
	if (dot_vec3(in_base_plnae, in_base_plnae) > pow(cy.diameter / 2.0, 2.0))
		return (0);
	if (hit->d == d1)
		hit->normal = cy.normal;
	else
		hit->normal = scale_vec3(cy.normal, -1.0);
	return (1);
}

t_hit	check_ray_collison_cylinder(t_ray ray, t_object obj)
{
	t_hit	hit;

	if (check_ray_cylinder_base_plane(ray, obj.cylinder, &hit) \
		|| check_ray_cylinder_side(ray, obj.cylinder, &hit))
		return (hit);
	else
		hit.d = -1.0;
	return (hit);
}
