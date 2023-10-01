/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:18:45 by hcho2             #+#    #+#             */
/*   Updated: 2023/10/01 18:34:18 by phan             ###   ########.fr       */
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
	// t_vec3	tmp;

	ratio = (double)(WIDTH) / HEIGHT;
	// printf("x, y axis: ");
	x_axis = scale_vec3(cam.axis[0], cam.fov * 2.0 * ratio);
	// print_vec3(x_axis);
	y_axis = scale_vec3(cam.axis[1], cam.fov * 2.0);
	// print_vec3(y_axis);
	// tmp = add_vec3(cam.point, scale_vec3(cam.dir, -1));
	left_top = add_vec3(scale_vec3(x_axis, -0.5), scale_vec3(y_axis, 0.5));
	left_top = add_vec3(cam.axis[2], left_top);
	// left_top = sub_vec3(left_top, cam.dir);
	// left_top = add_vec3(left_top, cam.point);
	change_x = div_vec3(x_axis, WIDTH);
	change_y = div_vec3(y_axis, HEIGHT);
	exchange_point = add_vec3(left_top, scale_vec3(change_x, x));
	exchange_point = add_vec3(exchange_point, scale_vec3(change_y, -1 * y));
	// exchange_point.x = left_top.x + (change_x.x * (x + 0.5) + change_y.x * (y + 0.5));
	// exchange_point.y = left_top.y - (change_x.y * (x + 0.5) + change_y.y * (y + 0.5));
	// if (cam.dir.y != 0.0)
	// 	exchange_point.z = left_top.z - (change_x.z * (x + 0.5) + change_y.z * (y + 0.5));
	// else
		// exchange_point.z = left_top.z + (change_x.z * (x + 0.5) + change_y.z * (y + 0.5));
	// exchange_point = add_vec3(exchange_point, cam.axis[2]);
	// printf("exchange_point: ");
	// print_vec3(exchange_point);
	return (exchange_point);
}

void	render_world(t_env env)
{
	t_ray ray;

	ft_memset(env.img.addr, 0, WIDTH * HEIGHT * (env.img.bits_per_pixel / 8));
	view_transform(env.rt.objs, env.rt.cam);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			ray.start = screen2world(env.rt.cam, x, y);
			ray.dir = unit_vec3(ray.start);
			ray.start = scale_vec3(ray.start, 0);
			put_pixel(&env.img, x, y, trace_ray(ray, env.rt.objs, env.rt.light.point));
		}
	}
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
}

int	main(int ac, char **av)
{
	t_env	env;
	// t_rt	rt;


	if (ac != 2)
	{
		write(1, "Error: Check your number of argument\n", 38);
		return (1);
	}
	env.rt.objs = NULL;
	parse_input(av[1], &env.rt);
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "miniRT");
	env.img.img = mlx_new_image(env.mlx, WIDTH, HEIGHT);
	env.img.addr = mlx_get_data_addr(env.img.img, &env.img.bits_per_pixel, &env.img.line_length, &env.img.endian);
	render_world(env);
	// mlx_mouse_hook(env.win, mouse_hook, &env);
	env.is_down = 0;
	mlx_hook(env.win, ON_KEYDOWN, 1L << 0, key_hook, &env);
	mlx_hook(env.win, ON_MOUSEDOWN, 1L << 0, mouse_down_hook, &env);
	mlx_hook(env.win, ON_MOUSEUP, 1L << 0, mouse_up_hook, &env);
	mlx_hook(env.win, ON_MOUSEMOVE, 1L << 0, mouse_move_hook, &env);
	mlx_hook(env.win, 17, 1L << 5, close_win, &env);
	mlx_loop(env.mlx);
}
