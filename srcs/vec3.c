/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:05:02 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/04 12:49:33 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_vec3(t_vec3 *v)
{
	printf("%f %f %f", v->x, v->y, v->z);
}

double	sqrlen_vec3(t_vec3 *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
}

double	len_vec3(t_vec3 *v)
{
	return (sqrt(sqrlen_vec3(v)));
}

t_vec3	add_vec3(t_vec3 *u, t_vec3 *v)
{
	t_vec3	ret;

	ret.x = u->x + v->x;
	ret.y = u->y + v->y;
	ret.z = u->z + v->z;
	return (ret);
}

void	div_vec3(double t, t_vec3 *v)
{
	v->x *= (1 / t);
	v->y *= (1 / t);
	v->z *= (1 / t);
}

void	scale_vec3(double t, t_vec3 *v)
{
	v->x *= t;
	v->y *= t;
	v->z *= t;
}

double	dot_vec3(t_vec3 *u, t_vec3 *v)
{
	return (u->x * v->x + u->y * v->y + u->z * v->z);
}

t_vec3	cross_vec3(t_vec3 *u, t_vec3 *v)
{
	t_vec3	ret;

	ret.x = u->x * v->z - u->z * v->y;
	ret.y = u->z * v->x - u->x * v->z;
	ret.z = u->x * v->y - u->y * v->z;
	return (ret);
}

t_vec3	unit_vec3(t_vec3 *v)
{
	t_vec3	unit;

	unit.x = v->x / len_vec3(v);
	unit.y = v->y / len_vec3(v);
	unit.z = v->z / len_vec3(v);
	return (unit);
}
