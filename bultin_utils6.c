/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:17:36 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 19:31:09 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_num_str(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	exit_not_num(t_cmd *cmd)
{
	printf("exit\n");
	printf("bash: exit: %s: numeric argument required\n", cmd->av[1]);
	exit(255);
}

void	ft_exit(t_info *s, t_cmd *cmd)
{
	int	ret;

	if (cmd->ac == 1)
	{
		printf("exit\n");
		exit(s->ret);
	}
	else if (cmd->ac == 2)
	{
		if (is_num_str(cmd->av[1]))
		{
			ret = ft_atoi(cmd->av[1]);
			printf("exit\n");
			exit(ret);
		}
		else
			exit_not_num(cmd);
	}
	else
	{
		printf("bash: exit: too many arguments\n");
		s->ret = 1;
	}
}


int		check_len(char *key, char *value, int has_equal)
{
	int len;

	len = 0;
	if (has_equal == FALSE)
	{
		len = ft_strlen(key) + 1;
	}
	else if (has_equal == TRUE)
	{
		if (value)
			len = ft_strlen(key) + ft_strlen(value) + 4;
		else
			len = ft_strlen(key) + 2;
	}
	return (len);
}