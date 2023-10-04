/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:59:40 by phan              #+#    #+#             */
/*   Updated: 2023/10/04 12:45:26 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	close_win(t_env *env)
{
	mlx_destroy_window(env->mlx, env->win);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_env *env)
{
	if (keycode == ESC)
		close_win(env);
	else if (keycode == W || keycode == A || keycode == S \
	|| keycode == D || keycode == SP || keycode == CTRL)
		translate_cam(keycode, env);
	return (0);
}

int	mouse_down_hook(int button, int x, int y, t_env *env)
{
	if (button == 1)
	{
		env->x = x;
		env->is_left_down = 1;
	}
	if (button == 2)
	{
		env->y = y;
		env->is_right_down = 1;
	}
	return (0);
}

int	mouse_up_hook(int button, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (button == 1)
		env->is_left_down = 0;
	if (button == 2)
		env->is_right_down = 0;
	return (0);
}

int	mouse_move_hook(int x, int y, t_env *env)
{
	double	theta;

	(void)x;
	(void)y;
	theta = 0.0001;
	if (env->is_left_down)
	{
		rotate_y(&env->rt.cam.axis[0], &env->rt.cam.axis[2], (x - env->x) * theta);
		render_world(*env);
	}
	if (env->is_right_down)
	{
		rotate_x(&env->rt.cam.axis[1], &env->rt.cam.axis[2], (y - env->y) * theta);
		render_world(*env);
		// char s1[100];
		// char s2[100];
		// char s3[100];
		// // char s3[100];
		// sprintf(s1, "(%f %f %f)", env->rt.cam.axis[0].x, env->rt.cam.axis[0].y, env->rt.cam.axis[0].z);
		// sprintf(s2, "(%f %f %f)", env->rt.cam.axis[1].x, env->rt.cam.axis[1].y, env->rt.cam.axis[1].z);
		// sprintf(s3, "(%f %f %f)", env->rt.cam.axis[2].x, env->rt.cam.axis[2].y, env->rt.cam.axis[2].z);
		// mlx_string_put(env->mlx, env->win, 30, 30, 0xffffff, s1);
		// mlx_string_put(env->mlx, env->win, 30, 50, 0xffffff, s2);
		// mlx_string_put(env->mlx, env->win, 30, 70, 0xffffff, s3);
	}
	return (0);
}
