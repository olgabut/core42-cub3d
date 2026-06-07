/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_list_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:49:09 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/07 17:33:01 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Free all map_lists
*/
void	free_map_list(t_map_list *head)
{
	t_map_list	*map_list;
	t_map_list	*next_map_list;

	map_list = head;
	while (map_list != NULL)
	{
		next_map_list = map_list->next;
		if (map_list->line)
		{
			free(map_list->line);
			map_list->line = NULL;
		}
		free(map_list);
		map_list = next_map_list;
	}
}

/*
	Creates new map_list by type and string line
	Return
		1 - ok
		0 - malloc error
*/
int	create_map_list(t_map_list **map_list, char *line)
{
	t_map_list	*new_map_list;

	new_map_list = ft_calloc(1, sizeof(t_map_list));
	if (!new_map_list)
		return (0);
	new_map_list->line = line;
	new_map_list->next = NULL;
	*map_list = new_map_list;
	return (1);
}

/*
	Adds new_map_list to the list of map_lists to the last position,
	where head is the first map_list
*/
void	add_new_map_list(t_map_list **head, t_map_list *new_map_list)
{
	t_map_list	*map_list;

	if (new_map_list == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new_map_list;
		return ;
	}
	map_list = *head;
	while (map_list->next != NULL)
		map_list = map_list->next;
	map_list->next = new_map_list;
}

t_map_list	*get_last_map_list(t_map_list *head)
{
	t_map_list	*map_list;

	if (!head)
		return (NULL);
	map_list = head;
	while (map_list->next != NULL)
		map_list = map_list->next;
	return (map_list);
}

void	print_map_list(t_map_list *head)
{
	t_map_list	*map_list;
	int i;

	map_list = head;
	printf("Print map_lists:\n");
	i = 1;
	while (map_list != NULL)
	{
		printf(" line=%d ", i);
		printf(" '%s'\n", map_list->line);
		map_list = map_list->next;
		i++;
	}
}