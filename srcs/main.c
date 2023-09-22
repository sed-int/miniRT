/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:18:45 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/22 22:54:16 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void put_pixel(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_vec3	screen2word(t_cam cam, int x, int y)
{
	t_vec3	exchange_point;
	double	radio;
	double	fov;

	radio = (double)WIDTH / HEIGHT;
	fov = tan((cam.view_angle / 2) * (M_PI / 180));
	exchange_point.x = (2 * ((x + 0.5) / WIDTH) - 1) * fov * radio;
	exchange_point.y = (1 - 2 * ((y + 0.5) / HEIGHT)) * fov;
	exchange_point.z = 0.0;
	return (add_vec3(exchange_point, cam.dir));
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

int	main(int ac, char **av)
{
	t_env       env;
	t_rt		rt;
	t_ray		ray;

	if (ac != 2)
	{
		write(1, "Error: Check your number of argument\n", 38);
		return (1);
	}
	parse_input(av[1], &rt);
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "miniRT");
	env.img.img = mlx_new_image(env.mlx, WIDTH, HEIGHT);
	env.img.addr = mlx_get_data_addr(env.img.img, &env.img.bits_per_pixel, &env.img.line_length, &env.img.endian);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			ray.start = screen2word(rt.cam, x, y);
			ray.dir = unit_vec3(sub_vec3(ray.start, scale_vec3(rt.cam.point, -1.0)));
			put_pixel(&env.img, x, y, trace_ray(ray, rt.objs, rt.light.point));
		}
	}
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
	mlx_hook(env.win, 17, 1L << 5, close_win, &env);
	mlx_loop(env.mlx);
}
