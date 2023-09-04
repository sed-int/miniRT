/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:59:21 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/04 13:06:26 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	at_ray(double t, t_ray *r)
{
	t_point3	ret;

	ret.x = r->org.x + t * r->dir.x;
	ret.y = r->org.y + t * r->dir.y;
	ret.z = r->org.z + t * r->dir.z;
	return (ret);
}
