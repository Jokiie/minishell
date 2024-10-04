/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodere <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 10:17:08 by ccodere           #+#    #+#             */
/*   Updated: 2024/06/10 02:17:57 by ccodere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Example
// void ft_lstprint(void *content)
//		printf("%s"\n, (char *)content);
// ft_lstiter(lst, ft_lstprint);
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*curr;

	if (!f)
		return ;
	curr = lst;
	while (curr != NULL)
	{
		f(curr->content);
		curr = curr->next;
	}
}
