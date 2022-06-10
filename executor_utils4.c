/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:25:47 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 19:27:11 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_path(t_cmd *cmd, char *str)
{
	char	*tmp;
	char	*tmp2;

	(void)cmd;
	(void)tmp;
	tmp = cmd->av[0];
	tmp2 = ft_strjoin(str, "/");
	if (!tmp2)
		exit(1);
	cmd->av[0] = ft_strjoin(tmp2, cmd->av[0]);
	if (!cmd->av[0])
		exit(1);
	free(tmp);
	free(tmp2);
}

void	free_path(t_path *path)
{
	t_path	*tmp;
	t_path	*next;

	tmp = path;
	while (tmp)
	{
		if (tmp->path)
			free(tmp->path);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	path = 0;
}