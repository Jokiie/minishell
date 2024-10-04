/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 09:57:04 by ccodere           #+#    #+#             */
/*   Updated: 2024/09/08 11:11:42 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Example
// t_list *lst = NULL;
// char str[6] = "Celia";
// t_list *node = ft_lstnew(str);
// ft_lstadd_back(&lst, node);
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else if (lst && new)
	{
		last = ft_lstlast(*lst);
		last->next = new;
		last->prev = last;
	}
}
