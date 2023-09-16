/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:23:07 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/16 16:11:57 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_count(int *count)
{
	count[AMBIENT] = 0;
	count[CAMERA] = 0;
	count[LIGHT] = 0;
}

int	check_type(char *type, int *count)
{
	int	type_len;
	int	ret;

	type_len = ft_strlen(type);
	if (!ft_strncmp(type, "A", type_len + 1) && count[AMBIENT]++ == 0)
		ret = AMBIENT;
	else if (!ft_strncmp(type, "C", type_len + 1) && count[CAMERA]++ == 0)
		ret = CAMERA;
	else if (!ft_strncmp(type, "L", type_len + 1) && count[LIGHT]++ == 0)
		ret = LIGHT;
	else if (!ft_strncmp(type, "sp", type_len + 1))
		ret = SPHERE;
	else if (!ft_strncmp(type, "pl", type_len + 1))
		ret = PLANE;
	else if (!ft_strncmp(type, "cy", type_len + 1))
		ret = CYLINDER;
	else
		exit(1);
	return (ret);
}

void	nl_to_null(char *line)
{
	char	*nl;

	nl = ft_strchr(line, '\n');
	if (nl)
		*nl = '\0';
}

int	parse_input(char *filename, void *env)
{
	int		fd;
	char	*line;
	char	**splitted;
	int		count[3];

	init_count(count);
	fd = open(filename, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		nl_to_null(line);
		splitted = ft_split(line, ' ');
		if (splitted)
			check_type(splitted[0], count);
	}
}
