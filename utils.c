/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:57:50 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 15:05:54 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_char(char *str)
{
	char	*tmp;
	int		len;
	int		i;

	if (str == 0)
		return (0);
	len = ft_strlen(str);
	if (!ft_calloc(len, sizeof(char), (void *)&tmp))
		exit(1);
	i = 0;
	while (str[i + 1])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[len - 1] = '\0';
	free(str);
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		tmp = 0;
	}
	str = tmp;
	return (str);
}

int	ft_isprint(int c)
{
	return (32 <= c && c <= 126);
}

void	print_element(t_info *s, char c)
{
	s->input = str_join_for_c(s->input, c);
	write(1, &c, 1);
}

char	*str_join_for_c(char *str, char c)
{
	char	*ret;
	int		i;

	if (!str)
	{
		if (!ft_calloc(2, sizeof(char), (void *)&ret))
			exit(1);
		ret[0] = c;
		ret[1] = '\0';
	}
	else
	{
		if (!ft_calloc(ft_strlen(str) + 2, sizeof(char), (void *)&ret))
			exit(1);
		i = -1;
		while (str[++i])
			ret[i] = str[i];
		ret[i] = c;
		ret[i + 1] = '\0';
		free(str);
	}
	return (ret);
}