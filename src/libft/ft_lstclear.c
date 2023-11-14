/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:42:41 by mgiovana          #+#    #+#             */
/*   Updated: 2022/10/24 14:50:23 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*prev;

	if (lst && *lst && del)
	{
		prev = (t_list *)*lst;
		while (prev)
		{
			temp = prev->next;
			ft_lstdelone(prev, del);
			prev = temp;
		}
		*lst = NULL;
	}
}
