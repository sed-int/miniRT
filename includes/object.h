/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunminjo <hyunminjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:46:36 by phan              #+#    #+#             */
/*   Updated: 2023/09/19 14:41:57 by hyunminjo        ###   ########.fr       */
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
}	t_object;

typedef struct	s_rt
{
	t_amb	amb;
	t_cam	cam;
	t_lgt	light;
	t_object *objs;
}	t_rt;

#endif