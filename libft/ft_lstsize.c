/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:32:17 by ccodere           #+#    #+#             */
/*   Updated: 2024/06/10 02:19:32 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*curr;
	int		size;

	if (lst)
	{
		size = 1;
		curr = lst;
		while (curr->next != NULL)
		{
			curr = curr->next;
			size++;
		}
		return (size);
	}
	else
		return (0);
}
