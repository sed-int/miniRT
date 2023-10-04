/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:30:39 by phan              #+#    #+#             */
/*   Updated: 2023/10/04 20:38:39 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rotate_y(t_vec3 *x, t_vec3 *z, double theta)
{
	t_vec3	prev_x;
	t_vec3	prev_z;

	prev_x = *x;
	prev_z = *z;
	*z = sub_vec3(\
		scale_vec3(prev_z, cos(theta)), \
		scale_vec3(prev_x, sin(theta)) \
	);
	*x = add_vec3(\
		scale_vec3(prev_x, cos(theta)), \
		scale_vec3(prev_z, sin(theta)) \
	);
}

void	rotate_x(t_vec3 *y, t_vec3 *z, double theta)
{
	t_vec3	prev_y;
	t_vec3	prev_z;

	prev_y = *y;
	prev_z = *z;
	*z = sub_vec3(\
		scale_vec3(prev_z, cos(theta)), \
		scale_vec3(prev_y, sin(theta)) \
	);
	*y = add_vec3(\
		scale_vec3(prev_y, cos(theta)), \
		scale_vec3(prev_z, sin(theta)) \
	);
}
