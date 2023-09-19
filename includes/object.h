/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:46:36 by phan              #+#    #+#             */
/*   Updated: 2023/09/19 17:10:56 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vec3.h"
# include "hit.h"
# include "ray.h"

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	normal;
	double	diameter;
	double	height;
}	t_cylinder;

typedef struct s_object
{
	t_vec3		amb;
	t_vec3		diffuse;
	t_vec3		specular;
	t_vec3		color;
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_hit		(*check_ray_collison)(t_ray, struct s_object);
	struct s_object	*next;
}	t_object;

// sphere
t_hit	check_ray_collison_sphere(t_ray ray, t_object obj);

// plane
t_hit	check_ray_collison_plane(t_ray ray, t_object obj);

// cylinder
t_hit	check_ray_collison_cylinder(t_ray ray, t_object obj);

#endif
