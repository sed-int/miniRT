/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:18:45 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/17 20:55:46 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void put_pixel(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_vec3	screen2word(int x, int y)
{
	t_vec3	exchange_point;
	double	radio;
	double	x_scale;
	double	y_scale;

	radio = (double)WIDTH / HEIGHT;
	x_scale = radio * 2 / WIDTH;
	y_scale = 2.0 / HEIGHT;
	exchange_point.x = -radio + x_scale * x;
	exchange_point.y = 1 - y_scale * y;
	exchange_point.z = 0.0;
	return (exchange_point);
}

unsigned int get_rgb(int r, int g, int b)
{
	if (r > 0xFF)
		r = 0xFF;
	if (g > 0xFF)
		g = 0xFF;
	if (b > 0xFF)
		b = 0xFF;
	return (0x00 << 24 | r << 16 | g << 8 | b);
}

t_hit	check_ray_collison_sphere(t_ray ray, t_object obj)
{
	t_hit	hit;
	t_vec3	tmp;
	double	b;
	double	c;
	double	nabla;

	hit.d = -1.0;
	tmp = sub_vec3(ray.start, obj.sphere.center);
	b = dot_vec3(ray.dir, tmp);
	c = dot_vec3(tmp, tmp) - obj.sphere.radius * obj.sphere.radius;
	nabla = b * b - c;
	if (nabla >= 0.0)
	{
		double d1 = -b + sqrtf(nabla);
		double d2 = -b - sqrtf(nabla);
		hit.d = ((d1 < d2 ) * d1) + ((d1 >= d2) * d2);
		hit.point = add_vec3(ray.start, scale_vec3(ray.dir, hit.d));
		hit.normal = unit_vec3(sub_vec3(hit.point, obj.sphere.center));
	}
	return (hit);
}

int check_ray_plane(t_ray ray, t_plane plane, t_vec3 *point, double *t)
{
    if (dot_vec3(plane.normal, scale_vec3(ray.dir, -1)) < 0.0)
        return (0);
    if (fabs(dot_vec3(plane.normal, ray.dir)) < 1e-2)
        return (0);
    *t = (dot_vec3(plane.normal, ray.start) - dot_vec3(plane.point, plane.normal)) / dot_vec3(ray.dir, plane.normal);
    if (*t < 0.0)
        return (0);
    *point = add_vec3(ray.start, scale_vec3(ray.dir, *t));
    return (1);
}

t_hit	check_ray_collison_plane(t_ray ray, t_object obj)
{
    t_hit	hit;
    t_vec3  point;
    double  t;

    hit.d = -1.0;
    if (check_ray_plane(ray, obj.plane, &point, &t))
    {
        hit.d = t;
        hit.point = point;
        hit.normal = obj.plane.normal;
    }
    return (hit);
}

int	is_over_cylinder_range(double h, double max)
{
	if (h < 0.0 || h > max)
		return (1);
	return (0);
}

int check_ray_cylinder_side(t_ray ray, t_cylinder cylinder, t_vec3 *point, t_vec3 *normal, double *d)
{
	double	a;
	double	b;
	double	c;
	double	nabla;
	t_vec3	vsub;

	vsub = sub_vec3(ray.start, cylinder.center);
	a = pow(dot_vec3(ray.dir, cylinder.normal), 2.0) - 1.0;
	b = dot_vec3(ray.dir, cylinder.normal) * dot_vec3(vsub, cylinder.normal) - dot_vec3(vsub, ray.dir);
	c = pow(cylinder.diameter / 2.0, 2.0f) - dot_vec3(vsub, vsub) + pow(dot_vec3(vsub, cylinder.normal), 2.0);
	nabla = b * b - a * c;
	if (nabla >= 0.0)
	{
		double d1 = (-b + sqrt(nabla)) / a;
		double d2 = (-b - sqrt(nabla)) / a;
		if (d1 < 0.0)
			*d = d2;
		else if (d2 < 0.0)
			*d = d1;
		else
			*d = ((d1 < d2) * d1) + ((d1 >= d2) * d2);
		*point = add_vec3(ray.start, scale_vec3(ray.dir, *d));
		if (is_over_cylinder_range(dot_vec3(sub_vec3(*point, cylinder.center), cylinder.normal), cylinder.height))
			return (0);
		*normal = unit_vec3(sub_vec3(sub_vec3(*point, cylinder.center), \
			scale_vec3(cylinder.normal, \
			dot_vec3(sub_vec3(*point, cylinder.center), cylinder.normal))));
		return (1);
	}
	return (0);
}

int check_ray_cylinder_base_plane(t_ray ray, t_cylinder cylinder, t_vec3 *point, t_vec3 *normal, double *d)
{
	t_vec3	in_base_plnae;

	if (dot_vec3(cylinder.normal, scale_vec3(ray.dir, -1)) < 0.0)
		return (0);
	if (fabs(dot_vec3(cylinder.normal, ray.dir)) < 1e-2)
		return (0);
	*d = (dot_vec3(add_vec3(scale_vec3(cylinder.normal, cylinder.height), cylinder.center), cylinder.normal) - dot_vec3(cylinder.normal, ray.start)) / dot_vec3(ray.dir, cylinder.normal);
	if (*d < 0.0)
		return (0);
	*point = add_vec3(ray.start, scale_vec3(ray.dir, *d));
	in_base_plnae = sub_vec3(sub_vec3(*point, cylinder.center), scale_vec3(cylinder.normal, \
		dot_vec3(sub_vec3(*point, cylinder.center), cylinder.normal)));
	if (dot_vec3(in_base_plnae, in_base_plnae) > pow(cylinder.diameter / 2, 2.0))
		return (0);
	*normal = cylinder.normal;
	return (1);
}

t_hit	check_ray_collison_cylinder(t_ray ray, t_object obj)
{
	t_hit	hit;
	t_vec3	point;
	t_vec3	normal;
	double	d;

	hit.d = -1.0;
	if (check_ray_cylinder_base_plane(ray, obj.cylinder, &point, &normal, &d) ||
		check_ray_cylinder_side(ray, obj.cylinder, &point, &normal, &d))
	{
		hit.d = d;
		hit.point = point;
		hit.normal = normal;
	}
	return (hit);
}

t_hit   find_closest_collisun(t_ray ray, t_object *objects)
{
    double  closest_d = 10000.0;
    t_hit   closest_hit;
    t_hit   hit;

    closest_hit.d = -1.0;
    for (int i = 0; i < 1; i++) {
		hit = objects[i].check_ray_collison(ray, objects[i]);
		if (hit.d >= 0.0 && hit.d < closest_d)
		{
			closest_d = hit.d;
			closest_hit = hit;
			closest_hit.obj = &objects[i];
		}
	}
	return (closest_hit);
}

int	trace_ray(t_ray ray, t_object *objects, t_light light_pos)
{
	t_hit		hit;
	t_object	obj;

    hit = find_closest_collisun(ray, objects);
	if (hit.d < 0)
		return (0);
	t_vec3	dir2light = unit_vec3(sub_vec3(light_pos, hit.point));
	double	diff = dot_vec3(dir2light, hit.normal);
	obj = *(hit.obj);
	diff = (diff >= 0.0) * diff;
	obj.diffuse = scale_vec3(obj.diffuse, diff);
	t_vec3	reflected_dir = \
		sub_vec3(\
		scale_vec3(hit.normal, dot_vec3(hit.normal, dir2light) * 2.0), \
		dir2light);
	double	spec = dot_vec3(scale_vec3(ray.dir, -1.0), reflected_dir);
	spec = (spec >= 0.0) * spec;
	spec = powf(spec, 9.0);
	obj.specular = scale_vec3(obj.specular, spec * 0.8);
	obj.color = add_vec3(add_vec3(obj.amb, obj.diffuse), obj.specular);
	return (get_rgb(obj.color.r, obj.color.g, obj.color.b));
}

t_object    set_sphere()
{
	t_object obj;

    obj.sphere.center = set_vec3(0.0, 0.0, 10.5);
    obj.sphere.radius = 3.0;
	obj.amb = set_vec3(255.0 * 0.2, 0, 0);
	obj.diffuse = set_vec3(255.0, 0.0, 0.0);
    obj.specular = set_vec3(255.0, 255.0, 255.0);
    obj.color = set_vec3(0.0, 0.0, 0.0);
    obj.check_ray_collison = check_ray_collison_sphere;
	return (obj);
}

t_object    set_plane()
{
    t_object obj;

    obj.plane.point = set_vec3(0.0, 0.5, 0.0);
    obj.plane.normal = set_vec3(0.0, 1.0, 0.0);
    obj.amb = set_vec3(0, 0, 255.0 * 0.2);
    obj.diffuse = set_vec3(0.0, 0.0, 255.0);
    obj.specular = set_vec3(255.0, 255.0, 255.0);
    obj.color = set_vec3(0.0, 0.0, 255.0);
    obj.check_ray_collison = check_ray_collison_plane;
    return (obj);
}

t_object	set_cylinder()
{
	t_object	obj;

	obj.cylinder.center = set_vec3(0.0, -30.0, 50.5);
	obj.cylinder.normal = set_vec3(0.0, 1.0, 0.0);
	obj.cylinder.diameter = 6.2;
	obj.cylinder.height = 10.42;
	obj.amb = set_vec3(0, 255.0 * 0.2, 0);
	obj.diffuse = set_vec3(0.0, 255.0, 0.0);
	obj.specular = set_vec3(255.0, 255.0, 255.0);
	obj.color = set_vec3(0.0, 0.0, 0.0);
	obj.check_ray_collison = check_ray_collison_cylinder;
	return (obj);
}

int close_win(t_env *env)
{
	mlx_destroy_window(env->mlx, env->win);
	exit(0);
	return (0);
}

int	main()
{
	t_env       env;
    t_object    sphere = set_sphere();
    t_object    plane = set_plane();
	t_object	cylinder = set_cylinder();
	t_ray		ray;
	t_light		light = set_vec3(0.0, 0.0, -1.5);
    t_vec3      eye_pos = set_vec3(0.0, 0.0, -1.5);
    t_object    objects[3];

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "miniRT");
	env.img.img = mlx_new_image(env.mlx, WIDTH, HEIGHT);
	env.img.addr = mlx_get_data_addr(env.img.img, &env.img.bits_per_pixel, &env.img.line_length, &env.img.endian);
	objects[0] = cylinder;
	objects[1] = plane;
	objects[2] = sphere;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			ray.start = screen2word(x, y);
			ray.dir = unit_vec3(sub_vec3(ray.start, eye_pos));
			put_pixel(&env.img, x, y, trace_ray(ray, objects, light));
		}
	}
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
	mlx_hook(env.win, 17, 1L << 5, close_win, &env);
	mlx_loop(env.mlx);
}
