/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:57:07 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/11 11:05:26 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
// # include "vec3.h"
# include "mlx.h"

# define WIDTH	1280
# define HEIGHT	720


typedef struct s_vec3
{
	union
	{
		struct
		{
			double x;
			double y;
			double z;
		};
		struct
		{
			double r;
			double g;
			double b;
		};
		double pos[3];
	};
}	t_vec3;

typedef t_vec3 t_light;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_ray
{
	t_vec3	start;	// ray의 시작 위치
	t_vec3	dir;	// ray의 방향 벡터 (unit vector)
}	t_ray;

typedef struct s_sphere
{
	t_vec3  center;
	double  radius;
}	t_sphere;

typedef struct s_plane
{
    t_vec3	point;
    t_vec3  normal;
}	t_plane;

typedef struct s_hit
{
    double	d;		// 광선의 시작 부터 충돌 지점까지의 거리
    t_vec3	point;	// 충돌 위치
    t_vec3	normal;	// 충돌 위치에서 평면의 수직 벡터 (unit vector)
    struct s_object    *obj; // 어떤 object에 충돌 했는지
}	t_hit;

typedef struct s_object
{
    t_vec3	amb;
    t_vec3	diffuse;
    t_vec3	specular;
    t_vec3	color;
    t_plane plane;
    t_sphere sphere;
    t_hit   (*check_ray_collison)(t_ray, struct s_object);
}   t_object;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_env;

/* vec3 */
void	print_vec3(t_vec3 v);
double	sqrlen_vec3(t_vec3 v);
double	len_vec3(t_vec3 v);
t_vec3	add_vec3(t_vec3 u, t_vec3 v);
t_vec3	sub_vec3(t_vec3 u, t_vec3 v);
t_vec3	scale_vec3(t_vec3 v, double t);
t_vec3	div_vec3(t_vec3 v, double t);
double	dot_vec3(t_vec3 u, t_vec3 v);
t_vec3	cross_vec3(t_vec3 u, t_vec3 v);
t_vec3	unit_vec3(t_vec3 v);
t_vec3	set_vec3(double x, double y, double z);

/* ray */
t_vec3	at_ray(double t, t_ray *r);

#endif
