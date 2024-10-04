/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <ccodere@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:10:24 by ccodere           #+#    #+#             */
/*   Updated: 2024/09/20 01:21:19 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Example
// char str[6] = "Celia";
// t_list *node = ft_lstnew(str);
t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = malloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->prev = NULL;
	if (content == NULL)
		lst->content = NULL;
	else
		lst->content = content;
	lst->next = NULL;
	return (lst);
}
