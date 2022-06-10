/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:39:14 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 15:40:41 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_backslash(t_info *s)
{
	int		flag;
	int		i;
	char	*str;

	if (s->input == 0 || ft_strlen(s->input) == 0)
		return (0);
	str = s->input;
	flag = -1;
	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] == '\\' && i >= 0)
	{
		flag *= -1;
		i--;
	}
	if (flag == 1)
	{
		s->input = del_char(str);
		return (1);
	}
	else
		return (0);
}

void	del_key(t_info *s)
{
	int	col;
	int	row;

	set_cursor(&col, &row);
	if (!s->input || (s->start.row >= row && s->start.col >= col))
		return ;
	col--;
	if (col < 0)
	{
		row -= 1;
		col = s->max.col;
	}
	tputs(tgoto(s->term.cm, col, row), 1, ft_putchar);//uznat
	tputs(s->term.ce, 1, ft_putchar);//uznat
	s->input = del_char(s->input);
}

void	init_terminal(t_info *s)
{
	tcgetattr(STDIN_FILENO, &s->term.term);
	s->term.term.c_lflag &= ~ICANON;
	s->term.term.c_lflag &= ~ECHO;
	s->term.term.c_cc[VMIN] = 1;
	s->term.term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &s->term.term);
	tgetent(NULL, "xterm");
	s->term.cm = tgetstr("cm", NULL);
	s->term.ce = tgetstr("ce", NULL);
}

void	key(t_info *s, int keycode)
{
	if (keycode == CNTRLD)
		end_of_file(s, s->input);
	else if (keycode == DEL)
		del_key(s);
	else if (keycode == UP)
		up(s);
	else if (keycode == DOWN)
		down(s);
	else
	{
		if (ft_isprint((char)keycode))
			print_element(s, (char)keycode);
	}
}

int		term_loop(t_info *s)
{
	int	c;

	set_cursor_windows(s);
	set_cursor(&s->cur.col, &s->cur.row);
	c = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (c == '\n')
		{
			write(1, "\n", 1);
			if (is_backslash(s))
				return (1);
			else
				return (0);
		}
		else
			key(s, c);
		c = 0;
	}
	return (0);
}