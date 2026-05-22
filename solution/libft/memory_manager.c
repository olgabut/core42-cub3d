/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:44:20 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/20 10:40:06 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	free_memory_links(t_memory_info **head)
{
	t_memory_info	*node;
	t_memory_info	*next_node;

	node = *head;
	while (node != NULL)
	{
		next_node = node->next;
		free(node->content);
		node->content = NULL;
		free(node);
		node = next_node;
	}
	*head = NULL;
}

int	create_memory_link_node(t_memory_info **new_memory_info, void *new_link)
{
	t_memory_info	*new_memory_info_node;

	if (!new_link)
		return (0);
	new_memory_info_node = malloc(sizeof(t_memory_info));
	if (!new_memory_info_node)
		return (0);
	new_memory_info_node->content = new_link;
	new_memory_info_node->next = NULL;
	*new_memory_info = new_memory_info_node;
	return (1);
}

/* Return:
	1 - ok
	0 - malloc error
 */
int	add_new_memory_link_for_control(t_memory_info **head, void *new_link)
{
	t_memory_info	*new_line_node;

	if (new_link == NULL)
		return (1);
	if (!create_memory_link_node(&new_line_node, new_link))
		return (0);
	ft_lstadd_front(head, new_line_node);
	return (1);
}
