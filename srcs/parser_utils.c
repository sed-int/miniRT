/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phan <phan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:50:22 by phan              #+#    #+#             */
/*   Updated: 2023/09/19 17:27:33 by phan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"

t_object	*new_obj()
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
