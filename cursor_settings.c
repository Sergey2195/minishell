/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:04:12 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 14:28:32 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_set_cursor(char buf[255], int *read_ret, int *i, int *flag)
{
	write(0, "\033[6n", 4);
	*read_ret = read(0, buf, 254);
	if (*read_ret < 0)
		*read_ret = 0;
	buf[*read_ret] = '\0';
	*i = 0;
	*flag = 0;
}

void	set_cursor(int *col, int *row)
{
	int		i;
	int		flag;
	char	buf[255];
	int		read_ret;

	init_set_cursor(buf, &read_ret, &i, &flag);
	while (buf[++i])
	{
		if ('0' <= buf[i] && buf[i] <= '9')
		{
			if (flag == 0)
				*row = ft_atoi(&buf[i]) - 1;
			else
			{
				*col = ft_atoi(&buf[i]) - 1;
				break ;
			}
			flag++;
			i += get_nbr_len(*row) - 1;
		}
	}
}

void	set_cursor_windows(t_info *s)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);//Функция ioctl манипулирует базовыми параметрами устройств, представленных в виде специальных файлов. TIOCGWINSZ     struct winsize *argp Определить размер окна.TIOCSWINSZ     const struct winsize *argp
	s->max.col = w.ws_col;
	s->max.row = w.ws_row;
	set_cursor(&s->start.col, &s->start.row);
}