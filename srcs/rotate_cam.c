/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:30:39 by phan              #+#    #+#             */
/*   Updated: 2023/10/01 16:25:17 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void rotate_x(t_vec3 *dir, double theta)
{
	double prev_x;
	double prev_y;
	double prev_z;

	prev_x = dir->x;
	prev_y = dir->y;
	prev_z = dir->z;
	dir->x = prev_x;
	dir->y = prev_y * cos(theta) - prev_z * sin(theta);
	dir->z = prev_y * sin(theta) + prev_z * cos(theta);
}

void rotate_y(t_vec3 *dir, double theta)
{
	double prev_x;
	double prev_y;
	double prev_z;

	prev_x = dir->x;
	prev_y = dir->y;
	prev_z = dir->z;
	dir->x = prev_x * cos(theta) - prev_z * sin(theta);
	dir->y = prev_y;
	dir->z = prev_x * sin(theta) + prev_z * cos(theta);
}

void rotate_z(t_vec3 *dir, double theta)
{
	double prev_x;
	double prev_y;
	double prev_z;

	prev_x = dir->x;
	prev_y = dir->y;
	prev_z = dir->z;
	dir->x = prev_x * cos(theta) - prev_y * sin(theta);
	dir->y = prev_x * sin(theta) + prev_y * cos(theta);
	dir->z = prev_z;
}