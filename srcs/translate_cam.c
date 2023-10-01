/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_cam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:31:16 by phan              #+#    #+#             */
/*   Updated: 2023/10/01 13:31:22 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void move_cam(t_rt *rt, t_vec3 delta)
{
	rt->cam.point = add_vec3(rt->cam.point, delta);
}

int translate_cam(int keycode, t_env *env)
{
	double delta = 0.3;

	if (keycode == W)
		move_cam(&(env->rt), set_vec3(0, 0, delta));
	else if (keycode == S)
		move_cam(&(env->rt), set_vec3(0, 0, -delta));
	else if (keycode == A)
		move_cam(&(env->rt), set_vec3(-delta, 0, 0));
	else if (keycode == D)
		move_cam(&(env->rt), set_vec3(delta, 0, 0));
	else if (keycode == SP)
		move_cam(&(env->rt), set_vec3(0, delta, 0));
	else if (keycode == CTRL)
		move_cam(&(env->rt), set_vec3(0, -delta, 0));
	print_vec3(env->rt.cam.point);
	render_world(*env);
	return (0);
}