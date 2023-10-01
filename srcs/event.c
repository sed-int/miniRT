/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:59:40 by phan              #+#    #+#             */
/*   Updated: 2023/10/01 17:30:19 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int close_win(t_env *env)
{
	mlx_destroy_window(env->mlx, env->win);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_env *env)
{
	printf("keycode: %d\n", keycode);
	if (keycode == ESC)
		close_win(env);
	else if (keycode == W || keycode == A || keycode == S || keycode == D || keycode == SP || keycode == CTRL)
		translate_cam(keycode, env);
	return (0);
}

int mouse_down_hook(int button, int x, int y, t_env *env)
{
	// int	start_x;
	// int start_y;
	
	(void)env;
	if (button == 1)
	{
		env->x = x;
		env->y = y;
	printf("start x: %d, y: %d\n", x, y);
		env->is_down = 1;
	}
	return (0);
}

int mouse_up_hook(int button, int x, int y, t_env *env)
{
	if (button == 1)
	{
		printf("end x: %d, y: %d\n", x, y);
		env->is_down = 0;
	}
	return(0);
}

int mouse_move_hook(int x, int y, t_env *env)
{
	
	(void)env;
	if (env->is_down)
	{
		// t_vec3 dir = set_vec3(0, 0, -1);
		printf("diff x: %d, y: %d\n", env->x - x, env->y - y);
		// if (dir.y != 0.0)
		// 	vup = set_vec3(0, 0, 1);
		// print_vec3(dir);
		// t_vec3 vup = set_vec3(0, 1, 0);
		// env->rt.cam.axis[2] = unit_vec3(dir);
		// env->rt.cam.axis[0] = unit_vec3(cross_vec3(vup, env->rt.cam.axis[2]));
		// env->rt.cam.axis[1] = unit_vec3(cross_vec3(env->rt.cam.axis[2], env->rt.cam.axis[0]));
		rotate_y(&(env->rt.cam.axis[0]), (x - env->x) * 0.001);
		rotate_y(&(env->rt.cam.axis[2]), (x - env->x) * 0.001);
		rotate_x(&(env->rt.cam.axis[1]), (y - env->y) * 0.001);
		rotate_x(&(env->rt.cam.axis[2]), (y - env->y) * 0.001);
		// env->rt.cam.dir = dir;
		render_world(*env);
	}
	return (0);
}