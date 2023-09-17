/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:05:02 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/16 18:54:46 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <stdio.h>
#include <math.h>

void	print_vec3(t_vec3 v)
{
	printf("%lf %lf %lf\n", v.x, v.y, v.z);
}

double	sqrlen_vec3(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	len_vec3(t_vec3 v)
{
	return (sqrt(sqrlen_vec3(v)));
}

t_vec3	add_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.x = u.x + v.x;
	ret.y = u.y + v.y;
	ret.z = u.z + v.z;
	return (ret);
}

t_vec3	sub_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3 ret;

	ret.x = u.x - v.x;
	ret.y = u.y - v.y;
	ret.z = u.z - v.z;
	return (ret);
}

t_vec3	div_vec3(t_vec3 v, double t)
{
	v.x *= (1 / t);
	v.y *= (1 / t);
	v.z *= (1 / t);
	return (v);
}

t_vec3	scale_vec3(t_vec3 v, double t)
{
	v.x *= t;
	v.y *= t;
	v.z *= t;
	return (v);
}

double	dot_vec3(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	cross_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.x = u.x * v.z - u.z * v.y;
	ret.y = u.z * v.x - u.x * v.z;
	ret.z = u.x * v.y - u.y * v.z;
	return (ret);
}

t_vec3	unit_vec3(t_vec3 v)
{
	t_vec3	unit;

	unit.x = v.x / len_vec3(v);
	unit.y = v.y / len_vec3(v);
	unit.z = v.z / len_vec3(v);
	return (unit);
}

t_vec3	set_vec3(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
