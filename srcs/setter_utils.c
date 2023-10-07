/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:08:59 by hcho2             #+#    #+#             */
/*   Updated: 2023/10/07 14:00:56 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	split_len(char **p)
{
	int	len;

	len = 0;
	while (p[len])
		len++;
	return (len);
}

void	set_dir(char *arg, t_vec3 *dir)
{
	char	**splitted;

	splitted = ft_split(arg, ',');
	if (split_len(splitted) != 3)
		exit(1);
	dir->x = atof(splitted[0]);
	dir->y = atof(splitted[1]);
	dir->z = atof(splitted[2]);
	if (dir->x > 1 || dir->x < -1 || \
		dir->y > 1 || dir->y < -1 || \
		dir->z > 1 || dir->z < -1)
		exit(1);
	free_split(splitted);
}

void	set_ratio(char *arg, double	*ratio)
{
	*ratio = atof(arg);
	if (*ratio < 0 || *ratio > 1)
		exit(1);
}
