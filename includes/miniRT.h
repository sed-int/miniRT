/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:57:07 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/04 13:06:31 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "vec3.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_ray
{
	t_vec3	org;
	t_vec3	dir;
}	t_ray;


/* vec3 */
void	print_vec3(t_vec3 *v);
double	sqrlen_vec3(t_vec3 *v);
double	len_vec3(t_vec3 *v);
t_vec3	add_vec3(t_vec3 *u, t_vec3 *v);
void	div_vec3(double t, t_vec3 *v);
void	scale_vec3(double t, t_vec3 *v);
double	dot_vec3(t_vec3 *u, t_vec3 *v);
t_vec3	cross_vec3(t_vec3 *u, t_vec3 *v);
t_vec3	unit_vec3(t_vec3 *v);

/* ray */
t_vec3	at_ray(double t, t_ray *r);

#endif
