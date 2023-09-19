/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:23:07 by hcho2             #+#    #+#             */
/*   Updated: 2023/09/18 12:22:42 by hcho2            ###   ########.fr       */
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
	int	ret;

	if (!ft_strcmp(type, "A") && count[AMBIENT]++ == 0)
		ret = AMBIENT;
	else if (!ft_strcmp(type, "C") && count[CAMERA]++ == 0)
		ret = CAMERA;
	else if (!ft_strcmp(type, "L") && count[LIGHT]++ == 0)
		ret = LIGHT;
	else if (!ft_strcmp(type, "sp"))
		ret = SPHERE;
	else if (!ft_strcmp(type, "pl"))
		ret = PLANE;
	else if (!ft_strcmp(type, "cy"))
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

void	check_filename(char *filename)
{
	int		len;
	char	**splitted;

	splitted = ft_split(filename, '.');
	len = 0;
	while (splitted[len++])
		;
	if (len != 2)
		exit(1);
	if (ft_strcmp(splitted[1], "rt"))
		exit(1);
}

int	parse_input(char *filename, void *env)
{
	int		fd;
	char	*line;
	char	**splitted;
	int		count[3];
	int		type;

	check_filename(filename);
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
			type = check_type(splitted[0], count);

	}
}