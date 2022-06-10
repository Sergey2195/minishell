/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:35:01 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 19:37:34 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_error(t_info *s, t_cmd *cmd, int type)
{
	if (type == 1)
	{
		printf("bash: %s: %s\n", cmd->av[0], strerror(errno));
		if (errno == 13)
			exit(126);
		else if (errno == 2)
			exit(127);
		exit(1);
	}
	else if (type == 2 || type == 4)
	{
		if (!find_env(s->env_head, "PATH"))
			type = 4;
		if (type == 2)
			printf("bash: %s: command not found\n", cmd->av[0]);
		else if (type == 4)
			printf("bash: %s: No such file or directory\n", cmd->av[0]);
		s->ret = 127;
	}
	else if (type == 3)
	{
		printf("bash: %s: is a directory\n", cmd->av[0]);
		s->ret = 126;
	}
}

int		find_simple_cmd(t_cmd *cmd, int *err)
{
	struct stat	buf;

	if (stat(cmd->av[0], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			*err = 3;
			return (0);
		}
		else
			return (1);
	}
	else
	{
		*err = 4;
		return (0);
	}
}