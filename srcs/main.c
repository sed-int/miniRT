/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:18:45 by hcho2             #+#    #+#             */
/*   Updated: 2023/10/01 08:52:22 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	put_pixel(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_vec3	screen2world(t_cam cam, int x, int y)
{
	t_vec3	exchange_point;
	double	ratio;
	t_vec3	x_axis;
	t_vec3	y_axis;
	t_vec3	left_top;
	t_vec3	change_x;
	t_vec3	change_y;

	ratio = (double)(WIDTH) / HEIGHT;
	printf("ratio: %lf\n", ratio);
	x_axis = scale_vec3(cam.axis[0], cam.fov * 2.0 * ratio);
	y_axis = scale_vec3(cam.axis[1], cam.fov * 2.0);
	// auto viewport_upper_left = center - (focal_length * w) - viewport_u/2 - viewport_v/2;
	left_top = add_vec3(scale_vec3(x_axis, -0.5), scale_vec3(y_axis, 0.5));
	// printf("left top: ");
	// print_vec3(left_top);
	change_x = div_vec3(x_axis, WIDTH);
	change_y = div_vec3(y_axis, HEIGHT);
	// printf("change_x : ");
	// print_vec3(change_x);
	// printf("change_y : ");
	// print_vec3(change_y);
	exchange_point.x = left_top.x + (change_x.x * (x + 0.5) + change_y.x * (y + 0.5)) + cam.axis[2].x;
	exchange_point.y = left_top.y - (change_x.y * (x + 0.5) + change_y.y * (y + 0.5)) - cam.axis[2].y;
	// exchange_point.x = left_top.x + (change_x.x * (x + 0.5) + change_y.x * (y + 0.5));
	// exchange_point.y = left_top.y - (change_x.y * (x + 0.5) + change_y.y * (y + 0.5));
	// exchange_point.x = (2 * ((x + 0.5) / WIDTH) - 1) * cam.fov * ratio;
	// exchange_point.y = (1 - 2 * ((y + 0.5) / HEIGHT)) * cam.fov;
	// exchange_point.x = cam.center.x - (WIDTH / 2.0) * ratio * cam.fov + ((x + 0.5)/ WIDTH) * cam.fov * ratio;
	// printf("%f\n", exchange_point.x);
	// exchange_point.y = cam.center.y - (HEIGHT / 2.0) * cam.fov + ((y + 0.5)/ HEIGHT) * cam.fov;
	// exchange_point.z = cam.axis[2].z;
	exchange_point.z = left_top.z + (change_x.z * (x + 0.5) + change_y.z * (y + 0.5)) + cam.axis[2].z;
	// return (add_vec3(exchange_point, cam.dir));
	// printf("%0.2f %0.2f\n", exchange_point.x, exchange_point.y);
	printf("exchange point: ");
	print_vec3(exchange_point);
	return (exchange_point);
}

// t_object	set_sphere()
// {
// 	t_object	obj;

// 	obj.sphere.center = set_vec3(0.0, 0.0, 10.5);
// 	obj.sphere.radius = 3.0;
// 	obj.amb = set_vec3(255.0 * 0.2, 0, 0);
// 	obj.diffuse = set_vec3(255.0, 0.0, 0.0);
// 	obj.specular = set_vec3(255.0, 255.0, 255.0);
// 	obj.color = set_vec3(0.0, 0.0, 0.0);
// 	obj.check_ray_collison = check_ray_collison_sphere;
// 	return (obj);
// }

// t_object	set_plane(void)
// {
// 	t_object	obj;

// 	obj.plane.point = set_vec3(0.0, 0.5, 0.0);
// 	obj.plane.normal = set_vec3(0.0, 1.0, 0.0);
// 	obj.amb = set_vec3(0, 0, 255.0 * 0.2);
// 	obj.diffuse = set_vec3(0.0, 0.0, 255.0);
// 	obj.specular = set_vec3(255.0, 255.0, 255.0);
// 	obj.color = set_vec3(0.0, 0.0, 255.0);
// 	obj.check_ray_collison = check_ray_collison_plane;
// 	return (obj);
// }

// t_object	set_cylinder()
// {
// 	t_object	obj;

// 	obj.cylinder.center = set_vec3(0.0, -30.0, 50.5);
// 	obj.cylinder.normal = set_vec3(0.0, 1.0, 0.0);
// 	obj.cylinder.diameter = 6.2;
// 	obj.cylinder.height = 10.42;
// 	obj.amb = set_vec3(0, 255.0 * 0.2, 0);
// 	obj.diffuse = set_vec3(0.0, 255.0, 0.0);
// 	obj.specular = set_vec3(255.0, 255.0, 255.0);
// 	obj.color = set_vec3(0.0, 0.0, 0.0);
// 	obj.check_ray_collison = check_ray_collison_cylinder;
// 	return (obj);
// }

int	close_win(t_env *env)
{
	mlx_destroy_window(env->mlx, env->win);
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_env	env;
	t_rt	rt;
	t_ray	ray;

	if (ac != 2)
	{
		write(1, "Error: Check your number of argument\n", 38);
		return (1);
	}
	rt.objs = NULL;
	parse_input(av[1], &rt);
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "miniRT");
	env.img.img = mlx_new_image(env.mlx, WIDTH, HEIGHT);
	env.img.addr = mlx_get_data_addr(env.img.img, &env.img.bits_per_pixel, &env.img.line_length, &env.img.endian);
	view_transform(rt.objs, rt.cam);
	// print_vec3(rt.objs->sphere.center);
	rt.cam.point = set_vec3(0, 0, 0);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			ray.start = screen2world(rt.cam, x, y);
			ray.dir = unit_vec3(sub_vec3(ray.start, rt.cam.point));
			put_pixel(&env.img, x, y, trace_ray(ray, rt.objs, rt.light.point));
		}
	}
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
	mlx_hook(env.win, 17, 1L << 5, close_win, &env);
	mlx_loop(env.mlx);
}
