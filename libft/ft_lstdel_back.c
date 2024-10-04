/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:44:57 by ccodere           #+#    #+#             */
/*   Updated: 2024/09/20 01:21:00 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_back(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp == NULL)
		return ;
	if (tmp->next == NULL)
	{
		free(tmp);
		*lst = NULL;
		return ;
	}
}
