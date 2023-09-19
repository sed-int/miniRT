/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:49:47 by phan              #+#    #+#             */
/*   Updated: 2023/09/19 16:04:22 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct s_ray
{
	t_vec3	start; // ray의 시작 위치
	t_vec3	dir;	  // ray의 방향 벡터 (unit vector)
}	t_ray;

int	trace_ray(t_ray ray, t_object *objects, t_light light_pos);

#endif
