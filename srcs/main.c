/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:18:45 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/10 17:28:41 by phan             ###   ########.fr       */
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

t_hit	intersection_ray_collison(t_ray ray, t_sphere sphere)
{
	t_hit	hit = {-1.0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
	t_vec3	tmp;
	double	b;
	double	c;
	double	nabla;

	tmp = sub_vec3(ray.start, sphere.center);
	b = dot_vec3(ray.dir, tmp);
	c = dot_vec3(tmp, tmp) - sphere.radius * sphere.radius;
	nabla = b * b - c;
	if (nabla > 0.0)
	{
		double d1 = -b + sqrtf(nabla);
		double d2 = -b - sqrtf(nabla);
		hit.d = ((d1 < d2 ) * d1) + ((d1 > d2) * d2);
		hit.point = add_vec3(ray.start, scale_vec3(ray.dir, hit.d));
		hit.normal = unit_vec3(sub_vec3(hit.point, sphere.center));
	}
	else if (nabla == 0.0)
	{
		hit.d = -b;
		hit.point = add_vec3(ray.start, scale_vec3(ray.dir, hit.d));
		hit.normal = unit_vec3(sub_vec3(hit.point, sphere.center));
	}
	return (hit);
}

int	trace_ray(t_ray ray, t_sphere sphere, t_light light)
{
	t_hit	hit;

	hit = intersection_ray_collison(ray, sphere);
	if (hit.d < 0)
		return (0);
	else
	{
		t_vec3	dir2light = unit_vec3(sub_vec3(light.pos, hit.point));
		double	diff = dot_vec3(dir2light, hit.normal);

		if (diff < 0.0)
			diff = 0.0;
		sphere.diffuse = scale_vec3(sphere.diffuse, diff);
		t_vec3	reflected_dir = sub_vec3(scale_vec3(hit.normal, dot_vec3(hit.normal, dir2light) * 2.0), dir2light);
		double	spec = dot_vec3(scale_vec3(ray.dir, -1.0), reflected_dir);
		if (spec < 0.0)
			spec = 0.0;
		spec = powf(spec, 9.0);
		sphere.specular = scale_vec3(sphere.specular, spec * 0.8);
		sphere.color = add_vec3(sphere.diffuse, sphere.specular);
		return (get_rgb(sphere.color.x, sphere.color.y, sphere.color.z));
	}
	// return (get_rgb(sphere.color.x * hit.d, sphere.color.y * hit.d, sphere.color.z * hit.d));
}

int	main()
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_sphere sphere = {
		{0.0, 0.0, 0.5},
		0.4,
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 255.0},
		{255.0, 255.0, 255.0},
		{0.0, 0.0, 0.0},
	};
	t_ray		ray;
	t_light		light = {{1.0, 1.0, -0.8}};

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			ray.start = screen2word(x, y);
			ray.dir = set_vec3(0.0, 0.0, 1.0);
			put_pixel(&img, x, y, trace_ray(ray, sphere, light));
		}
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}
