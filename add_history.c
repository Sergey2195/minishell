/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:28:03 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 18:32:39 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_buffer(t_save *save)
{
	if (save->prev != 0)
		save->prev->next = save->next;
	if (save->next != 0)
		save->next->prev = save->prev;
	free(save->input);
	free(save);
	save = 0;
}

t_save	*push_front_save(char *input, t_save *old_head, int flag)
{
	t_save	*new;

	new = 0;
	if (!ft_calloc(1, sizeof(t_save), (void *)&new))
		exit(1);
	new->input = ft_strdup(input);
	new->prev = 0;
	new->next = old_head;
	new->flag = flag;
	if (old_head != 0)
		old_head->prev = new;
	return (new);
}

void	reset_buffer(t_info *s)
{
	t_save	*tmp;

	if (s->save_head == 0)
		return ;
	while (s->save_head->prev)
		s->save_head = s->save_head->prev;
	tmp = s->save_head->next;
	if (s->save_head->flag == 0)
	{
		delete_buffer(s->save_head);
		s->save_head = tmp;
	}
	s->s_flag = 0;
}

void	save_history(t_info *s)
{
	reset_buffer(s);
	if (s->input == 0)
		return ;
	if (s->save_head == 0)
	{
		s->save_head = push_front_save(s->input, 0, 1);
	}
	else
	{
		s->save_head = push_front_save(s->input, s->save_head, 1);
	}
}