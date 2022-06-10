/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_bot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:12:43 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 18:19:28 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_cursor(t_info *s)
{
	t_keypos	pos;
	int			len;

	if (s->input != 0)
		len = ft_strlen(s->input);
	else
		len = 0;
	set_cursor(&pos.col, &pos.row);
	pos.col -= len;
	if (pos.col < 0)
	{
		pos.row--;
		pos.col = s->max.col + pos.col;
	}
	tputs(tgoto(s->term.cm, pos.col, pos.row), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
}

void	up(t_info *s)
{
	if (!s->save_head)
		return ;
	if (s->input != 0 && s->s_flag == 0)
		s->save_head = push_front_save(s->input, s->save_head, 0);
	if ((s->save_head->next != 0 && s->s_flag != 0) || s->save_head->flag == 0)
		s->save_head = s->save_head->next;
	s->s_flag = 1;
	move_cursor(s);
	write(1, s->save_head->input, ft_strlen(s->save_head->input));
	if (s->input != NULL)
		free(s->input);
	s->input = ft_strdup(s->save_head->input);	
}

void	down(t_info *s)
{
	if (s->save_head == 0 || (s->save_head->prev == 0
			&& s->save_head->flag == 0))
		return ;
	if (s->save_head->prev == 0)
		clear_prompt(s);
	else
	{
		s->save_head = s->save_head->prev;
		move_cursor(s);
		if (s->input)
			free(s->input);
		s->input = 0;
		write(1, s->save_head->input, ft_strlen(s->save_head->input));
		s->input = ft_strdup(s->save_head->input);
	}
}

void	clear_prompt(t_info *s)
{
	move_cursor(s);
	if (s->input)
		free(s->input);
	s->input = 0;
	s->s_flag = 0;
}