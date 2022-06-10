/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:40:10 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 18:18:32 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_file(t_info *s, char *input)
{
	if (input == NULL)
	{
		write(1, "exit\n", ft_strlen("exit\n"));
		tcsetattr(STDIN_FILENO, TCSANOW, &s->term.save);
		exit(0);
	}
}