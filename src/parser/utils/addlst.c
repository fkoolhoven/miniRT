#include "minirt.h"

void	add_plane(t_plane **head, t_plane *new)
{
	t_plane	*tmp;

	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_sphere(t_sphere **head, t_sphere *new)
{
	t_sphere	*tmp;

	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_cylinder(t_cylinder **head, t_cylinder *new)
{
	t_cylinder	*tmp;

	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}