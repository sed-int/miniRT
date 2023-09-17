/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:50:16 by phan              #+#    #+#             */
/*   Updated: 2023/09/16 18:51:36 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "vec3.h"

typedef struct s_hit
{
	double			d;		// 광선의 시작 부터 충돌 지점까지의 거리
	t_vec3			point;	// 충돌 위치
	t_vec3			normal;	// 충돌 위치에서 평면의 수직 벡터 (unit vector)
	struct s_object	*obj;	// 어떤 object에 충돌 했는지
} t_hit;

#endif