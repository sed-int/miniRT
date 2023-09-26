/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcho2 <hcho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:50:22 by phan              #+#    #+#             */
/*   Updated: 2023/09/26 13:11:16 by hcho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*new_obj(void)
{
	t_object	*tmp;

	tmp = (t_object *)malloc(sizeof(t_object));
	if (!tmp)
		exit(1);
	tmp->next = NULL;
	return (tmp);
}

void	obj_lstadd_back(t_object **lst, t_object *new)
{
	t_object	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
