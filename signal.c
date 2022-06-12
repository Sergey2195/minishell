/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:22:14 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/12 12:08:11 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig(int signal)
{
	if (signal == SIGINT)
	{
		if (g_info.is_fork == 0)
		{
			write(1, "\nbash> ", 7);
			if (g_info.input)
				free(g_info.input);
			g_info.input = 0;
			g_info.ret = 1;
		}
		else
		{
			g_info.ret = 130;
			write(1, "\n", 1);
		}
	}
	else
	{
		if (signal == SIGQUIT && g_info.is_fork == 1)
		{
			g_info.ret = 131;
			write(1, "Quit: 3\n", 9);
		}
	}
}
